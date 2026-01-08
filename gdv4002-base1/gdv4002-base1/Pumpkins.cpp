#include "Pumpkins.h"
#include "ctime"

//extern glm::vec2 force;

Pumpkin::Pumpkin(glm::vec2 initPosition, float initOrientation, glm::vec2 initSize, GLuint initTextureID, float mass, float angleChangePerSecond) : GameObject2D(initPosition, initOrientation, initSize, initTextureID)
{
	//variables
	this->mass = mass;
	velocity = glm::vec2(0.0f, 0.0f);

	this->angleChangePerSecond = angleChangePerSecond;
}

void Pumpkin::update(double tDelta)
{
	//update variable values
	glm::vec2 force = glm::vec2(0.005f, 0.0f);

	glm::vec2 F = force;

	glm::vec2 accel = F * (100.0f / mass);

	velocity = velocity + accel * (float)tDelta;

	position = position + velocity * (float)tDelta;

	orientation += angleChangePerSecond * (float)tDelta;
}