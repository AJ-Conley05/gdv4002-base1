#include "player.h"
#include "keys.h"
#include <bitset>

extern std::bitset<5> keys;
Player::Player(glm::vec2 initPosition, float initOrientation, glm::vec2 initSize, GLuint initTextureID, float mass) : GameObject2D(initPosition, initOrientation, initSize, initTextureID)
{
	this->mass = mass;

	velocity = glm::vec2(0.0f, 0.0f);


}

void Player::update(double tDelta) 
{
	glm::vec2 F = glm::vec2(0.0f, 0.0f);

	const float thrust = 0.5f;

	

	float player1RotationSpeed = glm::radians(180.0f);

	if (keys.test(Key::W) == true) {

		//F += glm::vec2(0.0f, thrust);
		F.y += thrust * sin(Player::orientation) * (float)tDelta;
		F.x += thrust * cos(Player::orientation) * (float)tDelta;
		
	}
	if (keys.test(Key::S) == true) {

		//F += glm::vec2(0.0f, -thrust);
		F.y -= thrust * sin(Player::orientation) * (float)tDelta;
		F.x -= thrust * cos(Player::orientation) * (float)tDelta;
		
	}
	if (keys.test(Key::A) == true) {

		Player::orientation += player1RotationSpeed * tDelta;

	}
	if (keys.test(Key::D) == true) {

		Player::orientation -= player1RotationSpeed * tDelta;
	}

	glm::vec2 a = F * (1.0f / mass);

	velocity = velocity + (a);

	if (glm::length(velocity) > MAX_SPEED) {
		velocity = glm::normalize(velocity);
		velocity *= MAX_SPEED;
	}

	position = position + (velocity);
}

