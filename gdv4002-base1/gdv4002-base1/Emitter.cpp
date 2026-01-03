#include "Emitter.h"
#include "engine.h"
#include "Bugs.h"

using namespace std;

Emitter::Emitter(glm::vec2 initPosition, glm::vec2 initSize, float emitTimeInterval) : GameObject2D(initPosition, 0.0f, initSize, 0)
{
	this->emitTimeInterval = emitTimeInterval;
	emitCounter = emitTimeInterval;

	particleNumber = 0;

	for (int i = 0; i < 8; i++)
	{

		string path = "Resources\\Textures\\BugFolder\\bug" + to_string(i + 1) + string(".png");
		bugs[i] = loadTexture(path.c_str());

		if (bugs[i] > 0)
			cout << "successfully loaded texture " << path << endl;
		else
			cout << "failed to load texture " << path << endl;
	}

	random_device rd;

	gen = mt19937(rd());

	spriteDist = uniform_int_distribution<int>(0, 7);
	normDist = uniform_real_distribution<float>(-1.0f, 1.0f);
	massDist = uniform_real_distribution<float>(0.005f, 0.08f);
	scaleDist = uniform_real_distribution<float>(10.0f, 14.0f);
}

void Emitter::render() 
{

}

void Emitter::update(double tDelta)
{
	emitCounter += (float) tDelta;

	while (emitCounter >= emitTimeInterval)
	{
		emitCounter -= emitTimeInterval;

		float x = position.x + normDist(gen) * size.x;
		float y = position.y + normDist(gen) * size.y;
		float scale = scaleDist(gen);
		float mass = massDist(gen);
		float rotationSpeed = glm::radians(normDist(gen) * 45.0f);
		int spriteIndex = spriteDist(gen);

		Bug* s1 = new Bug(glm::vec2(x, y), 0.0f, glm::vec2(scale, scale), bugs[spriteIndex], mass, rotationSpeed);

		string key = string("bug");

		if (particleNumber > 0)
		{
			key += to_string(particleNumber);
		}

		particleNumber++;

		addObject(key.c_str(), s1);
	}
}