//#include <CVK_2/CVK_Framework.h>
//
//#include <CVK_AnSim/CVK_AS_ShaderLineRender.h>
//#include <CVK_AnSim/CVK_AS_Line.h>
//#include <CVK_AnSim/CVK_AS_LineStrip.h>
//#include <CVK_AnSim/CVK_AS_CoordinateSystem.h>
//#include <CVK_AnSim/CVK_AS_HermiteSpline.h>
//#include <CVK_AnSim/CVK_AS_LineStrip.h>
//#include <time.h>
//#include <glm/gtc/random.hpp>
//#include <math.h>
//
//#define WIDTH 800
//#define HEIGHT 800
//
//#define PARTICLE_COUNT 200
//
//#define PARTICLE_GROUP_COUNT 10
//
//GLFWwindow* window;
//
////define Camera (Trackball)
//CVK::Perspective projection( 60.0f, WIDTH / (float) HEIGHT, 0.1f, 100.f);
//CVK::Trackball cam_trackball( WIDTH, HEIGHT, &projection);
//
//
//CVK::HermiteSpline *mPath;
//CVK::LineStrip* line;
//
//float aspect_ratio = (16.0/9.0);
//
//void resizeCallback( GLFWwindow *window, int w, int h)
//{
//	cam_trackball.setWidthHeight( w, h);
//	cam_trackball.getProjection()->updateRatio( w / (float) h);
//	glViewport( 0, 0, w, h);
//}
//
//void init_camera()
//{
//	//Camera
//	glm::vec3 v( 0.0f, 0.0f, 0.0f);
//	cam_trackball.setCenter( &v);
//	cam_trackball.setRadius( 5);
//	CVK::State::getInstance()->setCamera( &cam_trackball);
//}
//
//void init_scene()
//{
//	mPath = new CVK::HermiteSpline();
//
//	mPath->addControlPoint(new CVK::HermiteSplineControlPoint(glm::vec3(-5.0, 0.0, -5.0), glm::vec3(1.5, 5.0, 0.0)));
//	mPath->addControlPoint(new CVK::HermiteSplineControlPoint(glm::vec3(-3.0, 1.5, -1.0), glm::vec3(0.7, 4.0, 0.0)));
//	mPath->addControlPoint(new CVK::HermiteSplineControlPoint(glm::vec3(1.0, 2.0, 2.0), glm::vec3(0.3, -4.5, 0.0)));
//	mPath->addControlPoint(new CVK::HermiteSplineControlPoint(glm::vec3(5.0, 1.0, 5.0), glm::vec3(-0.3, 3.5, 0.0)));
//
//	mPath->generateRenderVertices();
//
//	line = new CVK::LineStrip();
//	line->setColor(glm::vec4(1,0,0,1));
//
//	for(int i = 0; i < mPath->getVerticesPtr()->size(); i++)
//	{
//		line->addPoint(mPath->getVerticesPtr()->at(i));
//	}
//}
//
//void drawHermiteSpline(CVK::ShaderLineRender *shader)
//{
//	//TODO
//	line->render(shader);
//}
//
//float randomFloat(float min, float max)
//{
//    float r = (float)rand() / (float)RAND_MAX;
//    return min + r * (max - min);
//}
//
//glm::vec3 random_vector(float min, float max){
//	return glm::vec3(randomFloat(min, max),randomFloat(min, max), randomFloat(min, max));
//}
//
int main()
{
//	// Init GLFW and GLEW
//	glfwInit();
//	CVK::useOpenGL33CoreProfile();
//	window = glfwCreateWindow(WIDTH, HEIGHT, "AnSim Exercise 1", 0, 0);
//	glfwSetWindowPos( window, 100, 50);
//	glfwMakeContextCurrent(window);
//	glfwSetWindowSizeCallback( window, resizeCallback);
//	glewInit();
//
//	CVK::State::getInstance()->setBackgroundColor( white);
//	glm::vec3 BgCol = CVK::State::getInstance()->getBackgroundColor();
//	glClearColor( BgCol.r, BgCol.g, BgCol.b, 0.0);
//	glEnable(GL_DEPTH_TEST);
//	glEnable(GL_BLEND);
//	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//
//	//load, compile and link Shader
//	const char *shadernames2[2] = { SHADERS_PATH "/ColorMVPShader.vert", SHADERS_PATH "/ColorMVPShader.frag" };
//	CVK::ShaderLineRender lineShader(VERTEX_SHADER_BIT | FRAGMENT_SHADER_BIT, shadernames2);
//	CVK::State::getInstance()->setShader(&lineShader);
//
//	init_camera();
//	init_scene();
//
//	glLineWidth(6);
//
//	CVK::CoordinateSystem coords = CVK::CoordinateSystem(glm::vec3(0.0f));
//
//	//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//
//	// Generate two buffers, bind them and initialize their data stores
//	GLuint* buffers;
//	GLuint position_buffer;
//	GLuint velocity_buffer;
//	GLuint compShader;
//	GLuint compute_prog;
//	GLuint render_prog;
//	GLuint velocity_tbo;
//	GLuint position_tbo;
//
//	compShader=glCreateShader(GL_COMPUTE_SHADER);
//	const char* compPath = SHADERS_PATH "/Particles.comp";
//	glShaderSource(compShader, 1, &compPath, 0);
//	glCompileShader(compShader);
//	compute_prog=glCreateProgram();
//	glAttachShader(compute_prog, compShader);
//	glLinkProgram(compute_prog);
//
//	compShader=glCreateShader(GL_COMPUTE_SHADER);
//	const char* compPath = SHADERS_PATH "/Particles.comp";
//	glShaderSource(compShader, 1, &compPath, 0);
//	glCompileShader(compShader);
//	compute_prog=glCreateProgram();
//	glAttachShader(compute_prog, compShader);
//	glLinkProgram(compute_prog);
//
//	glGenBuffers(2, buffers);
//	glBindBuffer(GL_ARRAY_BUFFER, position_buffer);
//	glBufferData(GL_ARRAY_BUFFER, PARTICLE_COUNT * sizeof(glm::vec4), NULL, GL_DYNAMIC_COPY);
//	// Map the position buffer and fill it with random vectors
//	glm::vec4 * positions = (glm::vec4 *)glMapBufferRange(GL_ARRAY_BUFFER, 0, PARTICLE_COUNT * sizeof(glm::vec4), GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT);
//	for (int i = 0; i < PARTICLE_COUNT; i++){
//		positions[i] = glm::vec4(random_vector(-10.0, 10.0), rand());
//		}
//	glUnmapBuffer(GL_ARRAY_BUFFER);
//
//	// Initialization of the velocity buffer - also filled with random vectors
//	glBindBuffer(GL_ARRAY_BUFFER, velocity_buffer);
//	glBufferData(GL_ARRAY_BUFFER,
//			PARTICLE_COUNT * sizeof(glm::vec4),
//			NULL,
//			GL_DYNAMIC_COPY);
//	glm::vec4 * velocities = (glm::vec4*)
//		glMapBufferRange(GL_ARRAY_BUFFER,
//				0,
//				PARTICLE_COUNT * sizeof(glm::vec4),
//				GL_MAP_WRITE_BIT |
//				GL_MAP_INVALIDATE_BUFFER_BIT);
//	for (int i = 0; i < PARTICLE_COUNT; i++)
//	{
//		velocities[i] = glm::vec4(random_vector(-0.1f, 0.1f), 0.0f);
//	}
//	glUnmapBuffer(GL_ARRAY_BUFFER);
//
//	glm::vec4 * attractor_masses;
//	float delta_time =0.0f;
//	float oldTime = glfwGetTime();
//	GLint dt_location = glGetUniformLocation(compute_prog, "dt");
//
////--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//	while( !glfwWindowShouldClose( window))
//	{
//		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//		float currentTime = glfwGetTime();
//		delta_time = currentTime - oldTime;
//		oldTime = currentTime;
//
//		// Update the buffer containing the attractor positions and masses
//		glm::vec4 * attractors =
//		(glm::vec4 *)glMapBufferRange(GL_UNIFORM_BUFFER,
//		0,
//		32 * sizeof(glm::vec4),
//		GL_MAP_WRITE_BIT |
//		GL_MAP_INVALIDATE_BUFFER_BIT);
//		int i;
//		for (i = 0; i < 32; i++)
//		{
//		attractors[i] =
//		glm::vec4(sin(currentTime * (i + 4) * 7.5 * 20.0) * 50.0f,
//		cos(currentTime * (float)(i + 7) * 3.9f * 20.0f) * 50.0f,
//		sin(currentTime * (float)(i + 3) * 5.3f * 20.0f) *
//		cos(currentTime * (float)(i + 5) * 9.1f) * 100.0f,
//		attractor_masses[i]);
//		}
//		glUnmapBuffer(GL_UNIFORM_BUFFER);
//		// Activate the compute program and bind the position
//		// and velocity buffers
//		glUseProgram(compute_prog);
//		glBindImageTexture(0, velocity_tbo, 0,
//		GL_FALSE, 0,
//		GL_READ_WRITE, GL_RGBA32F);
//		glBindImageTexture(1, position_tbo, 0,
//		GL_FALSE, 0,
//		GL_READ_WRITE, GL_RGBA32F);
//		// Set delta time
//		glUniform1f(dt_location, delta_time);
//		// Dispatch the compute shader
//		glDispatchCompute(PARTICLE_GROUP_COUNT, 1, 1);
//		// Ensure that writes by the compute shader have completed
//		glMemoryBarrier(GL_SHADER_IMAGE_ACCESS_BARRIER_BIT);
//		// Set up our mvp matrix for viewing
//		glm::mat4 mvp = glm::perspective(45.0f, aspect_ratio,
//		0.1f, 1000.0f) *glm::translate(mat4(1.0f), glm::vec3(0.0f, 0.0f, -60.0f)) *
//		glm::rotate(currentTime * 1000.0f,
//		glm::vec3(0.0f, 1.0f, 0.0f));
//		// Clear, select the rendering program and draw a full screen quad
//		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//		glUseProgram(render_prog);
//		glUniformMatrix4fv(0, 1, GL_FALSE, mvp);
//		glBindVertexArray(render_vao);
//		glEnable(GL_BLEND);
//		glBlendFunc(GL_ONE, GL_ONE);
//		glDrawArrays(GL_POINTS, 0, PARTICLE_COUNT);
//
//		//Update Camera
//		cam_trackball.update( window);
//
//		CVK::State::getInstance()->setShader(&lineShader);
//		lineShader.update();
//		coords.render(&lineShader);
//		drawHermiteSpline(&lineShader);
//
//		glfwSwapBuffers( window);
//		glfwPollEvents();
//	}
//	glfwDestroyWindow( window);
//	glfwTerminate();
	return 0;
}
//
