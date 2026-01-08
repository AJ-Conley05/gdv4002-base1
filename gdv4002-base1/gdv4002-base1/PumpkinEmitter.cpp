#include "PumpkinEmitter.h"
#include "engine.h"
#include "Pumpkins.h"

using namespace std;

//amount of pumpkins
extern int pumpkinLTD;

PumpkinEmitter::PumpkinEmitter(glm::vec2 initPosition, glm::vec2 initSize, float emitTimeInterval) : GameObject2D(initPosition, 0.0f, initSize, 0)
{
	

	this->emitTimeInterval = emitTimeInterval;
	emitCounter = emitTimeInterval;
	
	particleNumber = 0;
	pumpkinLTD = 0;
	
	//Assign textures
	for (int i = 0; i < 2; i++)
	{

		string path = "Resources\\Textures\\Pumpkins\\pumpkin" + to_string(i + 1) + string(".png");
		pumpkins[i] = loadTexture(path.c_str());

		if (pumpkins[i] > 0)
			cout << "successfully loaded texture " << path << endl;
		else
			cout << "failed to load texture " << path << endl;
	}

	//Setup the attribute distibution
	random_device rd;

	gen = mt19937(rd());

	spriteDist = uniform_int_distribution<int>(0, 1);
	normDist = uniform_real_distribution<float>(-1.0f, 1.0f);
	massDist = uniform_real_distribution<float>(0.4f, 0.8f);
	scaleDist = uniform_real_distribution<float>(10.0f, 40.0f);
}

void PumpkinEmitter::render()
{
	//do nothing
}

void PumpkinEmitter::update(double tDelta)
{
	emitCounter += (float)tDelta;


	//tells the emitter to only spawn objects when this varibale is less than a set amount
	if (pumpkinLTD < 5)
	{
		while (emitCounter >= emitTimeInterval)
		{
			emitCounter -= emitTimeInterval;

			//Assigns the objects their attributes
			float y = position.y + normDist(gen) * size.y;
			float x = position.x + normDist(gen) * size.x;
			float scale = scaleDist(gen);
			float mass = massDist(gen);
			float rotationSpeed = glm::radians(normDist(gen) * 45.0f);
			int spriteIndex = spriteDist(gen);

			//creates the object and adds one to the object count for the limiter
			Pumpkin* s1 = new Pumpkin(glm::vec2(y, x), 0.0f, glm::vec2(scale, scale), pumpkins[spriteIndex], mass, rotationSpeed);

			string key = string("pumpkin");

			if (particleNumber > 0)
			{
				key += to_string(particleNumber);
			}

			particleNumber++;
			pumpkinLTD++;

			addObject(key.c_str(), s1);
		}
	}
}