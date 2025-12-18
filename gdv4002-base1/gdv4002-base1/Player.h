#pragma once
#include "GameObject2D.h"
class Player : public GameObject2D 
{
private:
	/*float playerSpeed;*/
	float mass;
	glm::vec2 velocity;
	const float MAX_SPEED = 0.25f;
	const float NO_SPEED = 0.0f;
	const float SLOW_DOWN = 0.1f;

public:
	Player(glm::vec2 initPosition, float initOrientation, glm::vec2 initSize, GLuint initTextureID, float mass);
	void update(double tDelta) override;

};