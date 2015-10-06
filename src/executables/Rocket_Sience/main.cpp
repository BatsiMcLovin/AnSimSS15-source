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

//define dimensions for rocket and skybox
const float rocketScale = 7.5f;
const float semiAxisX = 3.0f;
const float semiAxisY = 1.0f;
const float semiAxisZ = 1.0f;

const float skyboxSize = 2000;

bool engine1Active=false;
bool engine2Active=false;
bool engine3Active=false;
bool engine4Active=false;
bool engine5Active=false;
bool engine6Active=false;
bool engine7Active=false;

//rocket can't go lower than this point
float lowestY = -skyboxSize+semiAxisX*rocketScale;

//for adjusting gravity
float gravity = 9.81f;


GLFWwindow* window;

//define Camera (Trackball)
CVK::Perspective projection(60.0f, width / (float) height, 0.1f, 10000.0f);
CVK::Trackball camera( width, height, &projection);


//*************************************************************************************************************
// space ship
CVK::MassPoint spaceShipMassPoint = CVK::MassPoint(glm::vec3(0.0f, 0.0f, 0.0f),  glm::vec3(0.0f, 0.0f, 0.0f), 272800.0*rocketScale);
Rocket rocket(spaceShipMassPoint.getMass(), spaceShipMassPoint.getPosition(), rocketScale*glm::vec3(3.0, 1.0, 1.0));

//*************************************************************************************************************

//initialize engines
ForceActor engine1(glm::vec3(0.0f, 0.f, 0.f), glm::vec3(0.0f, 0.0f, -rocketScale));
ForceActor engine2(glm::vec3(0.0f, 0.f, 0.f), glm::vec3(0.0f, 0.f, rocketScale));
ForceActor engine3(glm::vec3(0.0f, 0.f, 0.f), glm::vec3(0.0f, rocketScale, 0.0f));
ForceActor engine4(glm::vec3(0.0f, 0.f, 0.f), glm::vec3(0.0f, -rocketScale, 0.0f));
ForceActor engine5(glm::vec3(0.0f, 0.f, 0.f), glm::vec3(0.0f, rocketScale, 0.0f));
ForceActor engine6(glm::vec3(0.0f, 0.f, 0.f), glm::vec3(0.0f, -rocketScale, 0.0f));
ForceActor engine7(glm::vec3(0.0f, 0.f, 0.f), glm::vec3(-2.8*rocketScale, 0.0f, 0.0f));

//set material colors
CVK::Material engineMat(glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(1.0f), 100);
CVK::Material engineActiveMat(glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(1.0f), 100);

glm::vec3 redCol(1.0f, 0.0f, 0.0f);
glm::vec3 whiteCol(1.0f, 1.0f, 1.0f);

CVK::Node engineNode1;
CVK::Node engineNode2;
CVK::Node engineNode3;
CVK::Node engineNode4;
CVK::Node engineNode5;
CVK::Node engineNode6;
CVK::Node engineNode7;


void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
     if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {glfwDestroyWindow(window); exit(-1);};						//close the window

	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS){
		engine1.setForce(glm::vec3(1760000.0f, 0.0f, 0.0f));
		engine1Active=true;

	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_RELEASE){
			engine1.setForce(glm::vec3(0.0f, 0.0f, 0.0f));
			engine1Active=false;
		}

	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS){
		engine2.setForce(glm::vec3(1760000.0f, 0.0f, 0.0f));
		engine2Active=true;
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_RELEASE){
			engine2.setForce(glm::vec3(0.0f, 0.0f, 0.0f));
			engine2Active=false;
		}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS){
		engine3.setForce(glm::vec3(1760000.0f, 0.0f, 0.0f));
		engine3Active=true;
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_RELEASE){
			engine3.setForce(glm::vec3(0.0f, 0.0f, 0.0f));
			engine3Active=false;
		}
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS){
		engine4.setForce(glm::vec3(1760000.0f, 0.0f, 0.0f));
		engine4Active=true;
	}
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_RELEASE){
			engine4.setForce(glm::vec3(0.0f, 0.0f, 0.0f));
			engine4Active=false;
		}
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS){
		engine5.setForce(glm::vec3(0.0f, 0.0f, 1760000.0f));
		engine5Active=true;
	}
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_RELEASE){
			engine5.setForce(glm::vec3(0.0f, 0.0f, 0.0f));
			engine5Active=false;
		}
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS){
		engine6.setForce(glm::vec3(0.0f, 0.0f, 1760000.0f));
		engine6Active=true;
	}
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_RELEASE){
			engine6.setForce(glm::vec3(0.0f, 0.0f, 0.0f));
			engine6Active=false;
		}
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS){
		engine7.setForce(glm::vec3(30160000.0f, 0.0f, 0.0f));
		engine7Active=true;
	}
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_RELEASE){
			engine7.setForce(glm::vec3(0.0f, 0.0f, 0.0f));
			engine7Active=false;
		}
	if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS){
		rocket.reset(glm::vec3(0,lowestY,0), glm::quat(rocket.getStartingDirection()));
	}
	if (glfwGetKey(window, GLFW_KEY_0) == GLFW_PRESS){
		gravity = 0.0f;
		std::cout<<"gravity changed to "<<gravity<<std::endl;
	}
	if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS){
		gravity = 9.81f;
		std::cout<<"gravity changed to "<<gravity<<std::endl;
	}
	if (glfwGetKey(window, GLFW_KEY_KP_ADD) == GLFW_PRESS){
		gravity += 0.05;
	}
	if (glfwGetKey(window, GLFW_KEY_KP_SUBTRACT) == GLFW_PRESS){
		gravity -= 0.05;
	}
	if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS){
		rocket.printInfo();
		std::cout<<"gravity: "<<gravity<<"\n"<<std::endl;

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

void printControls(){
	std::cout<<"\nSteuerung"<<endl;
	std::cout<<"---------\n"<<endl;
	std::cout<<"W,S,A,D,Q,E: Rakete rotieren mittels Triebwerken"<<endl;
	std::cout<<"Space: Hauptantrieb starten"<<endl;
	std::cout<<"R: Rakete zurücksetzen"<<endl;
	std::cout<<"0: Schwerkraft auf 0 setzen"<<endl;
	std::cout<<"1: Schwerkraft auf 9.81 setzen"<<endl;
	std::cout<<"+/-: Schwerkraft erhöhen/verringern"<<endl;
	std::cout<<"I: Informationen auf Konsole ausgeben"<<endl;
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
    Skybox* skybox = new Skybox(skyboxSize);

	//Init scene nodes and mass points
	CVK::Node spaceship("Spaceship", RESOURCES_PATH "/sphere.obj");
	CVK::Material spaceshipMat(glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(1.0f), 100);
	spaceship.setMaterial(&spaceshipMat);
	//Init nodes for engines and add them to spaceship
	CVK::Node engineNode1("Engine1", RESOURCES_PATH "/engine.obj");
	CVK::Node engineNode2("Engine2", RESOURCES_PATH "/engine.obj");
	CVK::Node engineNode3("Engine3", RESOURCES_PATH "/engine.obj");
	CVK::Node engineNode4("Engine4", RESOURCES_PATH "/engine.obj");
	CVK::Node engineNode5("Engine5", RESOURCES_PATH "/engine.obj");
	CVK::Node engineNode6("Engine6", RESOURCES_PATH "/engine.obj");
	CVK::Node engineNode7("Engine7", RESOURCES_PATH "/engine.obj");
	spaceship.addChild(&engineNode1);
	spaceship.addChild(&engineNode2);
	spaceship.addChild(&engineNode3);
	spaceship.addChild(&engineNode4);
	spaceship.addChild(&engineNode5);
	spaceship.addChild(&engineNode6);
	spaceship.addChild(&engineNode7);

	//CVK::Material engineActive(RESOURCES_PATH "/engineActive.mtl", 1.0);

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
	camera.setRadius(120.0f);
	CVK::State::getInstance()->setCamera( &camera);

	printControls();

	float deltaTime = 0.0f;
	float oldTime = glfwGetTime();
	float t = 0.0f;

	while(!glfwWindowShouldClose( window))
	{	
		float currentTime = glfwGetTime();
		deltaTime = currentTime - oldTime;
		oldTime = currentTime;
		calculateFPS(1.0, "OpenGL Window");

		rocket.iterate(deltaTime, gravity);
		rocketPos = rocket.getPosition();

		//set modelMatrix
		glm::mat3 rotationMatrix = rocket.getRotationMat();
		glm::mat4 modelmatrix = glm::mat4(glm::vec4(rotationMatrix[0], 0.0f),
								glm::vec4(rotationMatrix[1],0.0f),
								glm::vec4(rotationMatrix[2], 0.0f),
								glm::vec4(0.f,0.f,0.f,1.f));
		modelmatrix = glm::translate(glm::mat4(1.0f), rocketPos) * modelmatrix;
		modelmatrix = glm::scale(modelmatrix, glm::vec3(rocketScale, rocketScale, rocketScale));
		spaceship.setModelMatrix(modelmatrix);

		engineNode1.setModelMatrix(glm::translate(glm::mat4(1.0f), engine1.getPosition()/rocketScale));
		engineNode2.setModelMatrix(glm::translate(glm::mat4(1.0f), engine2.getPosition()/rocketScale));
		engineNode3.setModelMatrix(glm::translate(glm::mat4(1.0f), engine3.getPosition()/rocketScale));
		engineNode4.setModelMatrix(glm::translate(glm::mat4(1.0f), engine4.getPosition()/rocketScale));
		engineNode5.setModelMatrix(glm::translate(glm::mat4(1.0f), engine5.getPosition()/rocketScale));
		engineNode6.setModelMatrix(glm::translate(glm::mat4(1.0f), engine6.getPosition()/rocketScale));
		engineNode7.setModelMatrix(glm::scale(glm::translate(glm::mat4(1.0f), engine7.getPosition()/rocketScale), glm::vec3(2, 2, 2)));

		if(rocketPos.y <= lowestY){
			rocket.reset(glm::vec3(rocketPos.x, lowestY, rocketPos.z), rocket.getRotationQuat());
		}

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		//update camera position and render
		camera.setCenter(&rocketPos);
		//Update Camera
		camera.update(window);

		//Use the skybox shader program
		CVK::State::getInstance()->setShader(&skyboxShader);
		CVK::State::getInstance()->getShader()->update();
		skybox->render();

		//Use phong shader to render the scene
		CVK::State::getInstance()->setShader(&spaceShader);
		CVK::State::getInstance()->setLight(0, &light);


		//Problem liegt im CVK: eine Zeile(122) einkommentiert -> nichts ändert sich, auskommentiert-->alle engines ändern sich
//		glm::vec3 engine1Color = engine1Active ? glm::vec3(1.0, 0.0, 0.0) : glm::vec3(1.0f);
//		engineNode1.getMaterial()->setdiffColor(engine1Color);
//		glm::vec3 engine2Color = engine2Active ? glm::vec3(1.0, 0.0, 0.0) : glm::vec3(1.0f);
//		engineNode2.getMaterial()->setdiffColor(engine1Color);


		//changes Material for all engines...
//		if(engine1Active){
//			engineNode1.getMaterial()->setdiffColor(redCol);
//		}
//		else engineNode1.getMaterial()->setdiffColor(whiteCol);

		//crash
//		if(engine2Active){
//			engineNode2.getMaterial()->setdiffColor(redCol);
//		}
//		else engineNode2.getMaterial()->setdiffColor(whiteCol);


		//CVK::Material currentMat1 = engine1Active ? engineActiveMat : engineMat;
		//engineNode1.setMaterial(&currentMat1);
		spaceShader.update();

		spaceship.render();

		glfwSwapBuffers( window);
		glfwPollEvents();
	}

	glfwDestroyWindow( window);
	glfwTerminate();


	return 0;
}

