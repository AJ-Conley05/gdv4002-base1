#pragma once

#include "GameObject2D.h"
#include "player.h"
#include <random>

class BulletEmitter : public GameObject2D
{
private:

	//variables for the class
	float emitTimeInterval;
	float emitCounter;

	unsigned long long particleNumber;

	GLuint bullets[2];

	Player* playerRef;

	std::mt19937 gen;

	std::uniform_int_distribution<int> spriteDist;

	std::uniform_real_distribution<float> normDist;
	std::uniform_real_distribution<float> massDist, scaleDist;

public:
	//functions for the class
	BulletEmitter(glm::vec2 initPosition, glm::vec2 initSize, float emitTImeInterval);

	void update(double tDelta) override;
	void render() override;
};