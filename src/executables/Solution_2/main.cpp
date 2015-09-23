#include <CVK_2/CVK_Framework.h>

#include <CVK_AnSim/CVK_AS_ShaderLineRender.h>
#include <CVK_AnSim/CVK_AS_Line.h>
#include <CVK_AnSim/CVK_AS_LineStrip.h>
#include <CVK_AnSim/CVK_AS_CoordinateSystem.h>
#include <CVK_AnSim/CVK_AS_HermiteSpline.h>
#include <CVK_AnSim/CVK_AS_LineStrip.h>

const int width = 640;
const int height = 480;

GLFWwindow* window;

//define Camera (Trackball)
CVK::Perspective projection(60.0f, width / (float) height, 0.1f, 30.0f);
CVK::Trackball camera( width, height, &projection);


CVK::HermiteSpline *spline;
CVK::LineStrip *line;

//*************************************************************************************************************
float timeRunning 	= 0.0f;
float position 		= 0.0f;
float speed 		= 10.0f;
glm::vec3 renderPosition = glm::vec3(0.0f,0.0f,0.0f);
glm::vec3 tangent 		 = glm::vec3(1.0f,0.0f,0.0f);
glm::vec3 normal		 = glm::vec3(0.0f,1.0f,0.0f);
glm::vec3 binormal		 = glm::vec3(0.0f,0.0f,1.0f);
//*************************************************************************************************************


void updateTeapot(float d_t)
{

	//*************************************************************************************************************
	//TODO Aufgabe 5 (b)
	//Berechnen Sie aus der verstrichenen Zeit und der Geschwindigkeit die Position des 
	//Teapots auf dem Spline und speichern Sie diese in der globalen Variable teapotPosition
	//*************************************************************************************************************

	timeRunning += d_t;
	position = timeRunning * speed;

	float u;
	int patchNum;
	spline->getParameterByArcLength(position, u, patchNum);
	if(u < 0.0f){ //wenn der Teapot am Ende des Pfades angekommen ist wird er an die Ausgangsposition zurückgesetzt
		position = 0.0f;
		timeRunning = 0.0f;
		return;
	}

	//jetzt  haben wir Parameter u und den index des entsprechenden Splines, nun können wir diesen evaluieren
	//und erhalten die Position des Teekessels. 
	glm::vec3 t;
	spline->evaluateHermiteSpline(u, 
							    (*(spline->getControlPointsPtr()))[patchNum],
								(*(spline->getControlPointsPtr()))[patchNum + 1],
								renderPosition, 
								t);

	//*************************************************************************************************************
	//TODO Aufgabe 5 (c)
	// Berechnen Sie die Orientierung des Teapots mittels der Frenet Frame Methode. 
	//*************************************************************************************************************
	
	//Orientierung des Teapots mittels der Frenet Frame Methode
	spline->calculateFrenetFrame(u, 
							   (*(spline->getControlPointsPtr()))[patchNum],
							   (*(spline->getControlPointsPtr()))[patchNum + 1],
							   tangent, 
							   binormal,
							   normal);

}


void resizeCallback( GLFWwindow *window, int w, int h)
{
	camera.setWidthHeight( w, h);
	camera.getProjection()->updateRatio( w / (float) h);
	glViewport( 0, 0, w, h);
}


void initSpline()
{	
	// Create a sample spline
	spline = new CVK::HermiteSpline();

	spline->addControlPoint(new CVK::HermiteSplineControlPoint(glm::vec3(-2.0, 0.0, 2.0), glm::vec3(6.0, 0.0, 0.0)));
	spline->addControlPoint(new CVK::HermiteSplineControlPoint(glm::vec3(-2.0, 0.0, -2.0), glm::vec3(-6.0, 0.0, 0.0)));
	spline->addControlPoint(new CVK::HermiteSplineControlPoint(glm::vec3(2.0, 2.0, 2.0), glm::vec3(6.0, 0.0, 0.0)));
	spline->addControlPoint(new CVK::HermiteSplineControlPoint(glm::vec3(2.0, 2.0, -2.0), glm::vec3(-6.0, 0.0, 0.0)));
	spline->addControlPoint(new CVK::HermiteSplineControlPoint(glm::vec3(2.0, 2.0, -2.0), glm::vec3(0.0, 0.0, 0.0)));

	spline->generateRenderVertices();

	// Create a line strip (in order to render the spline)
	line = new CVK::LineStrip();
	line->setColor(glm::vec4(1,0,0,1));
	for(int i = 0; i < spline->getVerticesPtr()->size(); i++)
	{
		line->addPoint(spline->getVerticesPtr()->at(i));
	}

	//*************************************************************************************************************
    renderPosition = (spline->getControlPointsPtr()->at(0))->getPosition();
	spline->generateArcLengthTable(100);
	//*************************************************************************************************************

}

int main() 
{
	// Init GLFW and GLEW
	glfwInit();
	CVK::useOpenGL33CoreProfile();
	window = glfwCreateWindow(width, height, "AnSim Exercise 2", 0, 0);
	glfwSetWindowPos(window, 100, 50);
	glfwMakeContextCurrent(window);
	glfwSetWindowSizeCallback(window, resizeCallback);
	glewInit();

	CVK::State::getInstance()->setBackgroundColor( white);
	glm::vec3 BgCol = CVK::State::getInstance()->getBackgroundColor();
	glClearColor( BgCol.r, BgCol.g, BgCol.b, 0.0);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);         
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);  

	//load, compile and link Shader
	const char *shadernames[2] = { SHADERS_PATH "/Phong.vert", SHADERS_PATH "/Phong.frag" };
	CVK::ShaderPhong phongShader(VERTEX_SHADER_BIT | FRAGMENT_SHADER_BIT, shadernames);
	
	const char *shadernames2[2] = { SHADERS_PATH "/ColorMVPShader.vert", SHADERS_PATH "/ColorMVPShader.frag" };
	CVK::ShaderLineRender lineShader(VERTEX_SHADER_BIT | FRAGMENT_SHADER_BIT, shadernames2);

	//Camera
	glm::vec3 center(0.0f, 0.0f, 0.0f);
	camera.setCenter(&center);
	camera.setRadius(6.0f);
	CVK::State::getInstance()->setCamera( &camera);

	//Light Sources
	CVK::Light light = CVK::Light(glm::vec4(0.0, 10.0, 0.0, 1.0), grey, glm::vec3(0, 0, 0), 1.0f, 0.0f);
	CVK::State::getInstance()->addLight(&light);
	CVK::State::getInstance()->updateSceneSettings(darkgrey, 0, white, 1, 10, 1);

	//Teapot 
	CVK::Node teapot("Teapot");
	CVK::Material material = CVK::Material(red, white, 100.0f);
	teapot.setMaterial(&material);
	CVK::Teapot geometry = CVK::Teapot();
	teapot.setGeometry(&geometry);

	//Coordinatesystem 
	CVK::CoordinateSystem coordinatesys(glm::vec3(0.0f));

	//Init spline (controllpoints and arc length table)
	initSpline();

	glLineWidth(6);
	float deltaTime = 0.0f;
	float oldTime = glfwGetTime();

	while(!glfwWindowShouldClose( window))
	{	
		float currentTime = glfwGetTime();
		deltaTime = currentTime - oldTime;
		oldTime = currentTime;

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		//Update Camera
		camera.update(window);

		updateTeapot(deltaTime);

		//Use phong shader to render the teapot
		CVK::State::getInstance()->setShader(&phongShader);
		CVK::State::getInstance()->setLight(0, &light);
		phongShader.update();

		//*************************************************************************************************************
		//TODO Aufgabe 5 (d)
		//Passen Sie die Modelmatrix und rendern Sie den Teapot an gewuenschter Position und Orientierung.
		//*************************************************************************************************************
		glm::mat4 modelmatrix = glm::transpose(glm::mat4(
								tangent.x, 	tangent.y, 	tangent.z, 	renderPosition.x,
								binormal.x, binormal.y, binormal.z, renderPosition.y,
								normal.x, 	normal.y, 	normal.z, 	renderPosition.z,
								0.0f,		0.0f,		0.0f,		1.0f));


		
		modelmatrix = glm::scale(modelmatrix, glm::vec3(0.5f,0.5f,0.5f));
		teapot.setModelMatrix(modelmatrix);
		teapot.render();

		//Draw coordinate system and hermite spline as line strip
		CVK::State::getInstance()->setShader(&lineShader);
		lineShader.update();
		coordinatesys.render(&lineShader);
		line->render(&lineShader);

		glfwSwapBuffers( window);
		glfwPollEvents();
	}

	glfwDestroyWindow( window);
	glfwTerminate();

	// Clean up
	delete line;
	delete spline;

	return 0;
}

