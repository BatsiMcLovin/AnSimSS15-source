#include <CVK_2/CVK_Framework.h>

#include <CVK_AnSim/CVK_AS_ShaderLineRender.h>
#include <CVK_AnSim/CVK_AS_Line.h>
#include <CVK_AnSim/CVK_AS_LineStrip.h>
#include <CVK_AnSim/CVK_AS_CoordinateSystem.h>
#include <CVK_AnSim/CVK_AS_HermiteSpline.h>
#include <CVK_AnSim/CVK_AS_LineStrip.h>

#define WIDTH 800
#define HEIGHT 800

#define PARTICLE_COUNT 200

GLFWwindow* window;

//define Camera (Trackball)
CVK::Perspective projection( 60.0f, WIDTH / (float) HEIGHT, 0.1f, 100.f);
CVK::Trackball cam_trackball( WIDTH, HEIGHT, &projection);


CVK::HermiteSpline *mPath;
CVK::LineStrip* line;



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

void init_scene()
{
	mPath = new CVK::HermiteSpline();

	mPath->addControlPoint(new CVK::HermiteSplineControlPoint(glm::vec3(-5.0, 0.0, -5.0), glm::vec3(1.5, 5.0, 0.0)));
	mPath->addControlPoint(new CVK::HermiteSplineControlPoint(glm::vec3(-3.0, 1.5, -1.0), glm::vec3(0.7, 4.0, 0.0)));
	mPath->addControlPoint(new CVK::HermiteSplineControlPoint(glm::vec3(1.0, 2.0, 2.0), glm::vec3(0.3, -4.5, 0.0)));
	mPath->addControlPoint(new CVK::HermiteSplineControlPoint(glm::vec3(5.0, 1.0, 5.0), glm::vec3(-0.3, 3.5, 0.0)));

	mPath->generateRenderVertices();

	line = new CVK::LineStrip();
	line->setColor(glm::vec4(1,0,0,1));

	for(int i = 0; i < mPath->getVerticesPtr()->size(); i++)
	{
		line->addPoint(mPath->getVerticesPtr()->at(i));
	}
}

void drawHermiteSpline(CVK::ShaderLineRender *shader)
{
	//TODO
	line->render(shader);
}

int main() 
{
	// Init GLFW and GLEW
	glfwInit();
	CVK::useOpenGL33CoreProfile();
	window = glfwCreateWindow(WIDTH, HEIGHT, "AnSim Exercise 1", 0, 0);
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
	const char *shadernames2[2] = { SHADERS_PATH "/ColorMVPShader.vert", SHADERS_PATH "/ColorMVPShader.frag" };
	CVK::ShaderLineRender lineShader(VERTEX_SHADER_BIT | FRAGMENT_SHADER_BIT, shadernames2);
	CVK::State::getInstance()->setShader(&lineShader);

	init_camera();
	init_scene();

	glLineWidth(6);

	CVK::CoordinateSystem coords = CVK::CoordinateSystem(glm::vec3(0.0f));
	
	while( !glfwWindowShouldClose( window))
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		//Update Camera
		cam_trackball.update( window);

		CVK::State::getInstance()->setShader(&lineShader);
		lineShader.update();
		coords.render(&lineShader);
		drawHermiteSpline(&lineShader);

		glfwSwapBuffers( window);
		glfwPollEvents();
	}
	glfwDestroyWindow( window);
	glfwTerminate();
	return 0;
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// Generate two buffers, bind them and initialize their data stores
	GLuint* buffers;
	GLuint position_buffer;

glGenBuffers(2, buffers);
glBindBuffer(GL_ARRAY_BUFFER, position_buffer);
glBufferData(GL_ARRAY_BUFFER, PARTICLE_COUNT * sizeof(glm::vec4), NULL, GL_DYNAMIC_COPY);
// Map the position buffer and fill it with random vectors
glm::vec4 * positions = (glm::vec4 *)glMapBufferRange(GL_ARRAY_BUFFER, 0, PARTICLE_COUNT * sizeof(glm::vec4), GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT);
for (int i = 0; i < PARTICLE_COUNT; i++){
	positions[i] = glm::vec4(random_vector(-10.0f, 10.0f), std::srand(time(Null))random_float());
	}
glUnmapBuffer(GL_ARRAY_BUFFER);

// Initialization of the velocity buffer - also filled with random vectors
glBindBuffer(GL_ARRAY_BUFFER, velocity_buffer);
glBufferData(GL_ARRAY_BUFFER,
PARTICLE_COUNT * sizeof(vmath::vec4),
NULL,
GL_DYNAMIC_COPY);
vmath::vec4 * velocities = (vmath::vec4 *)
glMapBufferRange(GL_ARRAY_BUFFER,
0,
PARTICLE_COUNT * sizeof(vmath::vec4),
GL_MAP_WRITE_BIT |
GL_MAP_INVALIDATE_BUFFER_BIT);
for (i = 0; i < PARTICLE_COUNT; i++)
{
velocities[i] = vmath::vec4(random_vector(-0.1f, 0.1f), 0.0f);
}
glUnmapBuffer(GL_ARRAY_BUFFER);

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
}

