#include "Bullets.h"

Bullet::Bullet(glm::vec2 initPosition, float initOrientation, glm::vec2 initSize, GLuint initTextureID, float mass, float angleChangePerSecond) : GameObject2D(initPosition, initOrientation, initSize, initTextureID)
{
	//variables
	this->mass = mass;
	velocity = glm::vec2(0.0f, 0.0f);


	this->angleChangePerSecond = angleChangePerSecond;
}

void Bullet::update(double tDelta)
{
	//update variable values
	glm::vec2 bulletForce = glm::vec2(-0.5f, 0.0f);

	glm::vec2 F = bulletForce;

	glm::vec2 accel = F * (0.5f / mass);

	velocity = velocity + accel * (float)tDelta;

	position = position + velocity * (float)tDelta;

	orientation += angleChangePerSecond * (float)tDelta;
}