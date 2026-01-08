#include "player.h"
#include "keys.h"
#include "Engine.h"
#include <bitset>

extern std::bitset<6> keys;
Player::Player(glm::vec2 initPosition, float initOrientation, glm::vec2 initSize, GLuint initTextureID, float mass) : GameObject2D(initPosition, initOrientation, initSize, initTextureID)
{
	//variables
	this->mass = mass;

	velocity = glm::vec2(0.0f, 0.0f);
}

void Player::update(double tDelta) 
{
	//create variables to update
	glm::vec2 F = glm::vec2(0.0f, 0.0f);

	const float thrust = 0.5f;

	float player1RotationSpeed = glm::radians(180.0f);

	//check if key is pressed if so do...
	if (keys.test(Key::W) == true)
	{
		//moves forward on the ships rotation
		F.y += thrust * sin(Player::orientation) * (float)tDelta;
		F.x += thrust * cos(Player::orientation) * (float)tDelta;
		
	}
	if (keys.test(Key::S) == true)
	{
		//moves backward on the ships rotation
		F.y -= thrust * sin(Player::orientation) * (float)tDelta;
		F.x -= thrust * cos(Player::orientation) * (float)tDelta;
		
	}
	if (keys.test(Key::A) == true)
	{
		//turns the player left
		Player::orientation += player1RotationSpeed * (float)tDelta;

	}
	if (keys.test(Key::D) == true)
	{
		//turns the player right
		Player::orientation -= player1RotationSpeed * (float)tDelta;
	}
	
	
	//velocity variables
	glm::vec2 a = F * (1.0f / mass);

	velocity = velocity + (a);

	//caps the speed
	if (glm::length(velocity) > MAX_SPEED) 
	{
		velocity = glm::normalize(velocity);
		velocity *= MAX_SPEED;
	}

	//slows down the ship to a stop
	if (keys.test(Key::LEFTSHIFT) == true)
	{
		velocity *= 0.9f;
	}
	
	//sets player position based on velocity
	position = position + (velocity);

	
	//If player goes off the right side appear on the left side
	if (Player::position.x >= 60)
	{
		Player::position.x = -60;
	}
	
	//if player goes off the left side appear on the right side
	if (Player::position.x <= -61)
	{
		Player::position.x = 60;
	}


	if (Player::position.y >= 60)
	{
		Player::position.y = -60;
	}

	if (Player::position.y <= -61)
	{
		Player::position.y = 60;
	}
}

