#include "Bugs.h"

extern glm::vec2 gravity;

Bug::Bug(glm::vec2 initPosition, float initOrientation, glm::vec2 initSize, GLuint initTextureID, float mass, float angleChangePerSecond) : GameObject2D(initPosition, initOrientation, initSize, initTextureID)
{
	this->mass = mass;
	velocity = glm::vec2(0.0f, 0.0f);
	
	/*angleChangePerSecond = glm::radians(45.0f);*/

	this->angleChangePerSecond = angleChangePerSecond;
}

void Bug::update(double tDelta)
{
	glm::vec2 F = gravity;

	glm::vec2 accel = F * (100.0f / mass);

	velocity = velocity + accel * (float)tDelta;

	position = position + velocity * (float)tDelta;

	orientation += angleChangePerSecond * (float)tDelta;
}