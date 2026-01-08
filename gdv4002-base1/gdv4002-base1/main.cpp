#include "Engine.h"
#include "Keys.h"
#include "Player.h"
#include "Emitter.h"
#include "PumpkinEmitter.h"
#include "BulletEmitter.h"
#include "Bullets.h"
#include <bitset>

// Function prototypes
void myKeyboardHandler(GLFWwindow* window, int key, int scancode, int action, int mods);
void myUpdate(GLFWwindow* window, double tDelta);
 
std::bitset<6> keys{ 0x0 };

//global variables
glm::vec2 gravity = glm::vec2(0.0f, -0.005);
int pumpkinLTD = 0;
int Shooting = 0;


int main(void)
{
	hideAxisLines();

	// Initialise the engine (create window, setup OpenGL backend)
	int initResult = engineInit("GDV4002 - Applied Maths for Games", 1024, 1024, 100.0f);

	// If the engine initialisation failed report error and exit
	if (initResult != 0) {

		printf("Cannot setup game window!!!\n");
		return initResult; // exit if setup failed
	}

	//making transparent backgrounds
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDepthFunc(GL_LEQUAL);
	
	
	//
	// Setup game scene objects here
	//

	//Background
	addObject("Background", glm::vec2(0, 0), 0, glm::vec2(100.0, 100.0), "Resources\\Textures\\Background.png");

	//Pumpkin Emitter
	PumpkinEmitter* Pemitter = new PumpkinEmitter(glm::vec2(0.0f, getViewplaneHeight() / 100.0f * -60.0f), glm::vec2(getViewplaneWidth() / 2.0f, 0.0f), 3.0f);

	addObject("PumpkinEmitter", Pemitter);

	//Bullet Emitter
	BulletEmitter* Bemitter = new BulletEmitter(glm::vec2(0.0f, getViewplaneHeight() / 4.0f * 1.2f), glm::vec2(getViewplaneWidth() / 100.0f, 0.0f), 0.5f);

	addObject("BulletEmitter", Bemitter);

	//Bug Emitter
	Emitter* emitter = new Emitter(glm::vec2(0.0f, getViewplaneHeight() / 2.0f * 1.2f), glm::vec2(getViewplaneWidth() / 2.0f, 0.0f), 0.05f);

	addObject("Emitter", emitter);

	//Player
	GLuint playerTexture = loadTexture("Resources\\Textures\\MySpaceship.png");

	Player* mainPlayer = new Player(glm::vec2(-1.5f, 0.0f), 0.0f, glm::vec2(10.0f, 10.0f), playerTexture, 1.0f);

	addObject("Player", mainPlayer);
	

	//functions
	setKeyboardHandler(myKeyboardHandler);
	setUpdateFunction(myUpdate, false);

	// Enter main loop - this handles update and render calls
	engineMainLoop();

	// When we quit (close window for example), clean up engine resources
	engineShutdown();

	// return success :)
	return 0;
}

void myUpdate(GLFWwindow* window, double tDelta)
{
	//wrap pumpkins/asteroids around the screen
	GameObjectCollection pumpkins = getObjectCollection("pumpkin");

	for (int i = 0; i < pumpkins.objectCount; i++)
	{

		if (pumpkins.objectArray[i]->position.x > (getViewplaneWidth() / 1.2f))
		{
			std::cout << "fuckers \n";
			pumpkins.objectArray[i]->position.x = -60;
			
		}
	}

	//Deletes the bugs
	GameObjectCollection bugs = getObjectCollection("bug");

	for (int i = 0; i < bugs.objectCount; i++)
	{

		if (bugs.objectArray[i]->position.y < -(getViewplaneHeight() / 1.2f))
		{
			
			deleteObject(bugs.objectArray[i]);
		}
	}

	//deletes bullets
	GameObjectCollection bullets = getObjectCollection("bullet");

	for (int i = 0; i < bullets.objectCount; i++)
	{

		if (bullets.objectArray[i]->position.x < -(getViewplaneWidth() / 1.2f))
		{

			deleteObject(bullets.objectArray[i]);
		}
	}


	//attaches bullet emitter onto the player
	GameObject2D* playerShip = getObject("Player");
	GameObject2D* BulletEmitter = getObject("BulletEmitter");
	BulletEmitter->position = playerShip->position;
}


void myKeyboardHandler(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	// Check if a key is pressed
	if (action == GLFW_PRESS)
	{

		// check which key was pressed...
		switch (key)
		{
		case GLFW_KEY_ESCAPE:
			// If escape is pressed tell GLFW we want to close the window (and quit)
			glfwSetWindowShouldClose(window, true);
			break;
				case GLFW_KEY_W:
					printf("w pressed\n");
					keys[Key::W] = true;
					break;
						case GLFW_KEY_S:
							printf("s pressed\n");
							keys[Key::S] = true;
							break;
								case GLFW_KEY_A:
									printf("a pressed\n");
									keys[Key::A] = true;
									break;
										case GLFW_KEY_D:
											printf("d pressed\n");
											keys[Key::D] = true;
											break;
												case GLFW_KEY_LEFT_SHIFT:
													printf("left shift pressed\n");
													keys[Key::LEFTSHIFT] = true;
													break;
														case GLFW_KEY_SPACE:
															printf("SPACE pressed\n");
															keys[Key::SPACE] = true;
															Shooting = 1;
															break;


		default:
		{
		}
		}
	}
	// If not check a key has been released
	else if (action == GLFW_RELEASE) 
	{
		// handle key release events
		switch (key)
		{
		case GLFW_KEY_W:
			printf("w released\n");
			keys[Key::W] = false;
			break;
				case GLFW_KEY_S:
					printf("s released\n");
					keys[Key::S] = false;
					break;
						case GLFW_KEY_A:
							printf("a released\n");
							keys[Key::A] = false;
							break;
								case GLFW_KEY_D:
									printf("d released\n");
									keys[Key::D] = false;
									break;
										case GLFW_KEY_LEFT_SHIFT:
											printf("left shift released\n");
											keys[Key::LEFTSHIFT] = false;
											break;
												case GLFW_KEY_SPACE:
													printf("SPACE released\n");
													keys[Key::SPACE] = false;
													Shooting = 0;
													break;
		}

	}
}

