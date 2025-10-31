#include "Engine.h"

// Function prototypes
void myUpdate(GLFWwindow* window, double tDelta);

void myUpdate(GLFWwindow* window, double tDelta)
{
	float player1RotationSpeed = glm::radians(90.0f);

	GameObject2D* player1Object = getObject("Player");
	player1Object->orientation += player1RotationSpeed * tDelta;
}

int main(void)
{
	float anglesPerSecond = glm::radians(45.0f);
	float playerCelocity = 2.0f;



	// Initialise the engine (create window, setup OpenGL backend)
	int initResult = engineInit("GDV4002 - Applied Maths for Games", 1024, 1024, 10.0f);

	// If the engine initialisation failed report error and exit
	if (initResult != 0) {

		printf("Cannot setup game window!!!\n");
		return initResult; // exit if setup failed
	}

	//
	// Setup game scene objects here
	//

	addObject("Player", glm::vec2(0, 0), 0,glm::vec2(0.5, 0.5), "Resources\\Textures\\player1_ship.png");
	
	GameObject2D* player1Object = getObject("Player");
	//player1Object->orientation += player1RotationSpeed * tDelta;

	if (player1Object != nullptr)
	{
		//update player 1 here
		player1Object->position = glm::vec2(-1.0f, 1.0f);


	}

	addObject("Player2", glm::vec2(0, 0), 0, glm::vec2(0.5, 0.5), "Resources\\Textures\\bumblebee.png");

	GameObject2D* player2Object = getObject("Player2");

	if (player2Object != nullptr)
	{
		//update player 1 here
		player2Object->position = glm::vec2(1.0f, 1.0f);

	}


	addObject("Pumpkin", glm::vec2(0, 0), 0, glm::vec2(2, 2), "Resources\\Textures\\pumpkin.png");
	
	addObject("Eyeball", glm::vec2(0, 0), 0, glm::vec2(0.5, 0.5), "Resources\\Textures\\eyeball.png");

	GameObject2D* eyeballObject = getObject("Eyeball");

	if (eyeballObject != nullptr)
	{
		//update player 1 here
		eyeballObject->position = glm::vec2(-2.0f, -1.0f);

	}

	setUpdateFunction(myUpdate);


	// Enter main loop - this handles update and render calls
	engineMainLoop();

	// When we quit (close window for example), clean up engine resources
	engineShutdown();

	// return success :)
	return 0;
}


