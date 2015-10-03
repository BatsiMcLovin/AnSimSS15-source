#include <CVK_2/CVK_Framework.h>
#include <CVK_AnSim/CVK_AS_MassPoint.h>
#include <CVK_AnSim/CVK_AS_ShaderSpace.h>

#include <iostream>
#include "Skybox.h"
#include "ShaderSkybox.h"
#include "Engine/RigidBody.h"
#include "Engine/Rocket.h"
#include "Engine/ForceActor.h"
#include "Engine/World.h"
#include "designPatterns/Singleton.h"

#include <sstream>


const int width = 1080;
const int height = 720;

GLFWwindow* window;

//define Camera (Trackball)
CVK::Perspective projection(60.0f, width / (float) height, 0.1f, 100.0f);
CVK::Trackball camera( width, height, &projection);


//*************************************************************************************************************
// space ship
CVK::MassPoint spaceShipMassPoint = CVK::MassPoint(glm::vec3(0.0f, 0.0f, 0.0f),  glm::vec3(0.0f, 0.0f, 0.0f), 757000.0);
float spaceShipEngineForce 	= 10.0f;
float spaceShipRotAngle		= 0.0f;  // angle in degree
Rocket rocket(spaceShipMassPoint.getMass(), spaceShipMassPoint.getPosition(), glm::vec3(3.0, 1.0, 1.0));

//*************************************************************************************************************

//initialize engines
ForceActor engine1(glm::vec3(0.0f, 0.f, 0.f), glm::vec3(0.0f, 0.0f, -1.0f));
ForceActor engine2(glm::vec3(0.0f, 0.f, 0.f), glm::vec3(0.0f, 0.f, 1.0f));
ForceActor engine3(glm::vec3(0.0f, 0.f, 0.f), glm::vec3(0.0f, 1.0f, 0.0f));
ForceActor engine4(glm::vec3(0.0f, 0.f, 0.f), glm::vec3(0.0f, -1.0f, 0.0f));
ForceActor engine5(glm::vec3(0.0f, 0.f, 0.f), glm::vec3(0.0f, 1.0f, 0.0f));
ForceActor engine6(glm::vec3(0.0f, 0.f, 0.f), glm::vec3(0.0f, -1.0f, 0.0f));
ForceActor engine7(glm::vec3(0.0f, 0.f, 0.f), glm::vec3(0.0f, 0.0f, 0.0f));

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
     if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {glfwDestroyWindow(window); exit(-1);};						//close the window

	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS){
		engine1.setForce(glm::vec3(1.0f, 0.0f, 0.0f));
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_RELEASE){
			engine1.setForce(glm::vec3(0.0f, 0.0f, 0.0f));
		}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS){
		engine2.setForce(glm::vec3(1.0f, 0.0f, 0.0f));
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_RELEASE){
			engine2.setForce(glm::vec3(0.0f, 0.0f, 0.0f));
		}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS){
		engine3.setForce(glm::vec3(1.0f, 0.0f, 0.0f));
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_RELEASE){
			engine3.setForce(glm::vec3(0.0f, 0.0f, 0.0f));
		}
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS){
		engine4.setForce(glm::vec3(1.0f, 0.0f, 0.0f));
	}
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_RELEASE){
			engine4.setForce(glm::vec3(0.0f, 0.0f, 0.0f));
		}
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS){
		engine5.setForce(glm::vec3(0.0f, 0.0f, 0.5f));
	}
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_RELEASE){
			engine5.setForce(glm::vec3(0.0f, 0.0f, 0.0f));
		}
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS){
		engine6.setForce(glm::vec3(0.0f, 0.0f, 0.5f));
	}
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_RELEASE){
			engine6.setForce(glm::vec3(0.0f, 0.0f, 0.0f));
		}
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS){
		engine7.setForce(glm::vec3(1760000.0f, 0.0f, 0.0f));
	}
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_RELEASE){
			engine7.setForce(glm::vec3(0.0f, 0.0f, 0.0f));
		}
	if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS){
		rocket.reset(glm::vec3(0,0,0));
	}
}

double calculateFPS(double interval = 1.0 , std::string title = "NONE"){
	static double tZero = glfwGetTime();
	static double fps = 0.0;

	static double frames = -1.0;

	frames ++;

	if (interval < 0.0)
		interval = 0.0;
	else
		if (interval > 10.0)
			interval = 10;

	double timeElapsed = glfwGetTime() - tZero;

	if (timeElapsed > interval){
		fps = frames / timeElapsed;
		if (title != "NONE"){
			std::ostringstream stream;
			stream << fps;
			std::string fpsToString = stream.str();

			title += " || Frames per second: " + fpsToString;

			const char* pszConstString = title.c_str();
			glfwSetWindowTitle(window, pszConstString);
		}
		else {
			// std::cout << "Frames per second: " + glm::to_string(fps) << endl;
		}
		frames = 0.0;
		tZero = glfwGetTime();
	}

	return fps;
}


void resizeCallback( GLFWwindow *window, int w, int h)
{
	camera.setWidthHeight( w, h);
	camera.getProjection()->updateRatio( w / (float) h);
	glViewport(0, 0, w, h);
}

int main() 
{
	// Init GLFW and GLEW
	glfwInit();
	CVK::useOpenGL33CoreProfile();
	window = glfwCreateWindow(width, height, "Rocket Science", 0, 0);
	glfwSetWindowPos(window, 100, 50);
	glfwMakeContextCurrent(window);
	glfwSetWindowSizeCallback(window, resizeCallback);
	glfwSetKeyCallback(window, keyCallback);
	glewInit();

	//set gravity; World Singleton does not work yet
	//World::getInstance()->setGravity(9.81);
	CVK::State::getInstance()->setBackgroundColor( white);
	glm::vec3 BgCol = CVK::State::getInstance()->getBackgroundColor();
	glClearColor( BgCol.r, BgCol.g, BgCol.b, 0.0);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);         
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);  

	//load, compile and link Shader
	const char *shadernames[2] = { SHADERS_PATH "/Toon.vert", SHADERS_PATH "/Toon.frag" };
	CVK::ShaderSpace spaceShader(VERTEX_SHADER_BIT | FRAGMENT_SHADER_BIT, shadernames);

    const char *skyboxShadernames[2] = {SHADERS_PATH "/Minimal.vert", SHADERS_PATH "/SimpleTexture.frag"};
    ShaderSkybox skyboxShader(VERTEX_SHADER_BIT | FRAGMENT_SHADER_BIT, skyboxShadernames);


	//Light Sources
	CVK::Light light = CVK::Light(glm::vec4(0.0, 10.0, 0.0, 1.0), grey, glm::vec3(0, 0, 0), 1.0f, 0.0f);
	CVK::State::getInstance()->addLight(&light);
	CVK::State::getInstance()->updateSceneSettings(darkgrey, 0, white, 1, 10, 1);

	// Create skybox
    Skybox* skybox = new Skybox(30.0f);

	//Init scene nodes and mass points
	CVK::Node spaceship("Spaceship", RESOURCES_PATH "/sphere.obj");
	//First mass point for the spaceship

	//Create Rocket and initialize engines as ForceActor
	rocket.addForce(&engine1);
	rocket.addForce(&engine2);
	rocket.addForce(&engine3);
	rocket.addForce(&engine4);
	rocket.addForce(&engine5);
	rocket.addForce(&engine6);
	rocket.addForce(&engine7);

	//Camera
	glm:: vec3 rocketPos(rocket.getPosition());
	camera.setCenter(&rocketPos);
	camera.setRadius(6.0f);
	CVK::State::getInstance()->setCamera( &camera);

	float deltaTime = 0.0f;
	float oldTime = glfwGetTime();
	float t = 0.0f;

	while(!glfwWindowShouldClose( window))
	{	
		float currentTime = glfwGetTime();
		deltaTime = currentTime - oldTime;
		oldTime = currentTime;
		calculateFPS(1.0, "OpenGL Window");

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		//Update Camera
		camera.update(window);

		//Use the skybox shader program
        CVK::State::getInstance()->setShader(&skyboxShader);
        CVK::State::getInstance()->getShader()->update();
        skybox->render();

		//Use phong shader to render the scene
		CVK::State::getInstance()->setShader(&spaceShader);
		CVK::State::getInstance()->setLight(0, &light);
		spaceShader.update();

		//Update physics
		//spaceShipMassPoint.numericIntegration(deltaTime);
		rocket.iterate(deltaTime);

		//set modelMatrix

		//TODO:hier stimmt was nicht mit der Rotation; Modell dreht sich, während Kamera immer geradeaus geht
		//glm::mat4 modelmatrix = glm::rotate(glm::mat4(1.0f), spaceShipRotAngle, glm::vec3(0.0f,1.0f,0.0f));
		glm::mat3 rotationMatrix = rocket.getRotationMat();
		glm::mat4 modelmatrix = glm::mat4(glm::vec4(rotationMatrix[0], 0.0f),
								glm::vec4(rotationMatrix[1],0.0f),
								glm::vec4(rotationMatrix[2], 0.0f),
								glm::vec4(0.f,0.f,0.f,1.f));
		modelmatrix = glm::translate(glm::mat4(1.0f), rocket.getPosition()) * modelmatrix;
		modelmatrix = glm::scale(modelmatrix, glm::vec3(1,1,1));
		spaceship.setModelMatrix(modelmatrix);

		//update camera position and render
		rocketPos = rocket.getPosition();
		camera.setCenter(&rocketPos);
		spaceship.render();
		
		t += deltaTime * 0.01f; //speed = 0.01
		if(t >= 1.0)
			t = 0.0f;

		glfwSwapBuffers( window);
		glfwPollEvents();
	}

	glfwDestroyWindow( window);
	glfwTerminate();


	return 0;
}

