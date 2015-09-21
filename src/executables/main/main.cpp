#include <CVK_2/CVK_Framework.h>

#include <CVK_AnSim/CVK_AS_ShaderLineRender.h>
#include <CVK_AnSim/CVK_AS_Line.h>
#include <CVK_AnSim/CVK_AS_LineStrip.h>
#include <CVK_AnSim/CVK_AS_CoordinateSystem.h>

const int WIDTH  = 600;
const int HEIGHT = 480;

GLFWwindow* window;

CVK::Node *scene_node;

CVK::Line *line;
CVK::LineStrip *lineStrip;


//define Camera (Trackball)
CVK::Perspective projection( 60.0f, WIDTH / (float) HEIGHT, 0.1f, 50.f);
CVK::Trackball cam_trackball( WIDTH, HEIGHT, &projection);

//define Lights
CVK::Light *plight;

//define materials
CVK::Material *mat_cvlogo, *mat_red;

float shininess = 100.0f;

void resizeCallback( GLFWwindow *window, int w, int h)
{
	cam_trackball.setWidthHeight( w, h);
	cam_trackball.getProjection()->updateRatio( w / (float) h);
	glViewport( 0, 0, w, h);
}

void init_camera()
{
	//Camera
	glm::vec3 v( 0.0f, 0.0f, 0.0f);
	cam_trackball.setCenter( &v);
	cam_trackball.setRadius( 5);
	CVK::State::getInstance()->setCamera( &cam_trackball);
}

void init_materials()
{
	mat_cvlogo = new CVK::Material(RESOURCES_PATH "/cv_logo.bmp", 1.f, 0.75, white, shininess);
	mat_red = new CVK::Material(red, white, shininess);
}

void init_scene()
{
	scene_node = new CVK::Node( "Scene");

	CVK::Teapot *teapot = new CVK::Teapot(); 

	CVK::Node *teapot_node_up = new CVK::Node("Teapot_up");
	teapot_node_up->setModelMatrix( glm::translate(glm::mat4( 1.0f), glm::vec3( 0, 0.72, 0)));
	teapot_node_up->setMaterial( mat_cvlogo);
	teapot_node_up->setGeometry( teapot);
	scene_node->addChild( teapot_node_up);
	
	CVK::Plane *plane = new CVK::Plane();
	
	CVK::Node *plane_node_up = new CVK::Node("plane_up");
	plane_node_up->setModelMatrix( glm::scale( glm::mat4( 1.0f), glm::vec3( 5, 5, 5)));
	plane_node_up->setMaterial( mat_red);
	plane_node_up->setGeometry( plane);
	scene_node->addChild( plane_node_up);

	line = new CVK::Line(glm::vec3(0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
	line->setColor(glm::vec4(0, 0, 1, 1));

	lineStrip = new CVK::LineStrip();
	lineStrip->setColor(glm::vec4(1, 1, 0, 1));
	lineStrip->addPoint(glm::vec3(0, 2, 0));
	lineStrip->addPoint(glm::vec3(2, 2, 0));
	lineStrip->addPoint(glm::vec3(2, 1, 0));
	lineStrip->addPoint(glm::vec3(0, 2, 0));

}

int main() 
{
	// Init GLFW and GLEW
	glfwInit();
	CVK::useOpenGL33CoreProfile();
	window = glfwCreateWindow(WIDTH, HEIGHT, "CVK_1 Example", 0, 0);
	glfwSetWindowPos( window, 100, 50);
	glfwMakeContextCurrent(window);
	glfwSetWindowSizeCallback( window, resizeCallback);
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
	CVK::State::getInstance()->setShader(&phongShader);
	const char *shadernames2[2] = { SHADERS_PATH "/ColorMVPShader.vert", SHADERS_PATH "/ColorMVPShader.frag" };
	CVK::ShaderLineRender lineShader(VERTEX_SHADER_BIT | FRAGMENT_SHADER_BIT, shadernames2);
	CVK::State::getInstance()->setShader(&lineShader);

	init_camera();
	init_materials();
	init_scene();

	//define Light Sources
	plight = new CVK::Light(glm::vec4(-1, 1, 1, 1), grey, glm::vec3(0, 0, 0), 1.0f, 0.0f);
	CVK::State::getInstance()->addLight(plight);
	CVK::State::getInstance()->updateSceneSettings(darkgrey, 0, white, 1, 10, 1);

	glLineWidth(6);

	CVK::CoordinateSystem coords = CVK::CoordinateSystem(glm::vec3(0.0f));
	
	while( !glfwWindowShouldClose( window))
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		//Update Camera
		cam_trackball.update( window);

		//Use Shader and define camera uniforms
		CVK::State::getInstance()->setShader(&phongShader);
		phongShader.update();

		//define Light uniforms
		CVK::State::getInstance()->setLight( 0, plight);

		scene_node->render();

		glClear(GL_DEPTH_BUFFER_BIT);
		CVK::State::getInstance()->setShader(&lineShader);
		lineShader.update();
		lineStrip->render(&lineShader);
		CVK::drawLine(&lineShader, glm::vec3(1, 1, 0), glm::vec3(1, 2, 0), glm::vec4(1, 0, 0, 1));
		line->render(&lineShader);
		coords.render(&lineShader);

		glfwSwapBuffers( window);
		glfwPollEvents();
	}
	glfwDestroyWindow( window);
	glfwTerminate();
	return 0;
}