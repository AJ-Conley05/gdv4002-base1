#pragma once
#include "GameObject2D.h"
class Player : public GameObject2D 
{
private:
	//variables
	float mass;
	glm::vec2 velocity;
	const float MAX_SPEED = 0.05f;
	

public:
	//functions
	Player(glm::vec2 initPosition, float initOrientation, glm::vec2 initSize, GLuint initTextureID, float mass);
	void update(double tDelta) override;

};