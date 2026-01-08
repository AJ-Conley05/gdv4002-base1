#pragma once

#include "GameObject2D.h"
#include "player.h"

class Bullet : public GameObject2D
{
private:
	//variables
	float mass;
	glm::vec2 velocity;

	float angleChangePerSecond;

public:
	//functions
	Bullet(glm::vec2 initPosition, float initOrientation, glm::vec2 initSize, GLuint initTextureID, float mass, float angleChangePerSecond);

	void update(double tDelta) override;
};