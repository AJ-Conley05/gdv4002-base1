#include "Engine.h"
#include "Keys.h"
#include "Player.h"
#include <bitset>


// Function prototypes
void myUpdate(GLFWwindow* window, double tDelta);
void myKeyboardHandler(GLFWwindow* window, int key, int scancode, int action, int mods);
float enemyPhase[3] = { 0.7f, 0.8f, 0.5f };
float enemyPhaseVelocity[3] = { glm::radians(64.0f), glm::radians(72.0f), glm::radians(90.0f) };
 

std::bitset<5> keys{ 0x0 };

int main(void)
{
	float anglesPerSecond = glm::radians(45.0f);
	float playerStartingOrientation = glm::radians(90.0f);
	float playerVelocity = 2.0f;
	float phase = 0.0f;

	hideAxisLines();




	// Initialise the engine (create window, setup OpenGL backend)
	int initResult = engineInit("GDV4002 - Applied Maths for Games", 1024, 1024, 10.0f);

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

	addObject("Background", glm::vec2(0, 0), 0, glm::vec2(10.0, 10.0), "Resources\\Textures\\Background.png");

	// player
	/*addObject("Player", glm::vec2(0, 0), playerStartingOrientation,glm::vec2(1.0, 1.0), "Resources\\Textures\\mySpaceship.png");*/

	GLuint playerTexture = loadTexture("Resources\\Textures\\mySpaceship.png");

	Player* mainPlayer = new Player(glm::vec2(-1.5f, 0.0f), 0.0f, glm::vec2(1.0f, 1.0f), playerTexture, 1.0f);

	addObject("Player", mainPlayer);

	
	GameObject2D* player1Object = getObject("Player");
	//player1Object->orientation += player1RotationSpeed * tDelta;

	if (player1Object != nullptr)
	{
		//update player 1 here
		player1Object->position = glm::vec2(-1.0f, 1.0f);


	}
	
	addObject("Eyeball", glm::vec2(0, 0), 0, glm::vec2(0.5, 0.5), "Resources\\Textures\\eyeball.png");

	GameObject2D* eyeballObject = getObject("Eyeball");

	if (eyeballObject != nullptr)
	{
		//update player 1 here
		eyeballObject->position = glm::vec2(-1.0f, -1.0f);

	}
	// enemy objects
	addObject("Pumpkin", glm::vec2(0, 0), 0, glm::vec2(2, 2), "Resources\\Textures\\pumpkin.png");
	addObject("Pumpkin", glm::vec2(2, 0), 0, glm::vec2(2, 2), "Resources\\Textures\\pumpkin.png");
	addObject("Pumpkin", glm::vec2(-2, 0), 0, glm::vec2(2, 2), "Resources\\Textures\\pumpkin.png");
	
	





	setUpdateFunction(myUpdate);
	setUpdateFunction(myUpdate);
	setKeyboardHandler(myKeyboardHandler);

	
	/*listGameObjectKeys();*/
	/*listObjectCounts();*/

	// Enter main loop - this handles update and render calls
	engineMainLoop();

	// When we quit (close window for example), clean up engine resources
	engineShutdown();

	// return success :)
	return 0;
}


void myUpdate(GLFWwindow* window, double tDelta)
{
	// player variables
	float player1RotationSpeed = glm::radians(180.0f);
	static float playerSpeed = 3.0f;
	

	GameObject2D* player1Object = getObject("Player");
	
	// enemies
	GameObjectCollection enemies = getObjectCollection("Pumpkin");

	for (int i = 0; i < enemies.objectCount; i++) {

		enemies.objectArray[i]->position.y = sinf(enemyPhase[i]); // assume phase stored in radians so no conversion needed

		enemyPhase[i] += enemyPhaseVelocity[i] * tDelta;
	}


	//Player move up

	if (keys.test(Key::W) == true)
	{
		player1Object->position.y += playerSpeed * tDelta;
		/*player1Object->position.y += playerSpeed * sin(player1Object->orientation) * (float)tDelta;
		player1Object->position.x += playerSpeed * cos(player1Object->orientation) * (float)tDelta;*/
		
		
	}

	//Player move down

	if (keys.test(Key::S) == true)
	{
		player1Object->position.y -= playerSpeed * tDelta;
		/*player1Object->position.y -= playerSpeed * sin(player1Object->orientation) * (float)tDelta;
		player1Object->position.x -= playerSpeed * cos(player1Object->orientation) * (float)tDelta;*/
	}

	//Player move left

	if (keys.test(Key::A) == true)
	{

		player1Object->orientation += player1RotationSpeed * tDelta;
	}

	//Player move right

	if (keys.test(Key::D) == true)
	{

		player1Object->orientation -= player1RotationSpeed * tDelta;
	}


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
		}

	}
}

