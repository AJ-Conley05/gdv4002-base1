#include "player.h"
#include "keys.h"
#include <bitset>

extern std::bitset<5> keys;
Player::Player(glm::vec2 initPosition, float initOrientation, glm::vec2 initSize, GLuint initTextureID, float initialPlayerSpeed) : GameObject2D(initPosition, initOrientation, initSize, initTextureID)
{

	playerSpeed = initialPlayerSpeed;

	velocity = glm::vec2(0.0f, 0.0f);
}

void Player::update(double tDelta) {

	if (keys.test(Key::W) == true) {

		position.y += playerSpeed * (float)tDelta;
	}
	if (keys.test(Key::S) == true) {

		position.y -= playerSpeed * (float)tDelta;
	}
	if (keys.test(Key::A) == true) {

		position.x -= playerSpeed * (float)tDelta;
	}
	if (keys.test(Key::D) == true) {

		position.x += playerSpeed * (float)tDelta;
	}
}

