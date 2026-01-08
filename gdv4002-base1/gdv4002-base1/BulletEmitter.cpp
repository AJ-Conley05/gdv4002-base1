#include "BulletEmitter.h"
#include "engine.h"
#include "Bullets.h"

using namespace std;

extern int Shooting;

BulletEmitter::BulletEmitter(glm::vec2 initPosition, glm::vec2 initSize, float emitTimeInterval) : GameObject2D(initPosition, 0.0f, initSize, 0)
{
	this->emitTimeInterval = emitTimeInterval;
	emitCounter = emitTimeInterval;

	particleNumber = 0;

	//Assign textures
	for (int i = 0; i < 2; i++)
	{

		string path = "Resources\\Textures\\BulletFolder\\Bullet" + to_string(i + 1) + string(".png");
		bullets[i] = loadTexture(path.c_str());

		if (bullets[i] > 0)
			cout << "successfully loaded texture " << path << endl;
		else
			cout << "failed to load texture " << path << endl;
	}

	//Setup the attribute distribution
	random_device rd;

	gen = mt19937(rd());

	spriteDist = uniform_int_distribution<int>(0, 1);
	normDist = uniform_real_distribution<float>(-1.0f, 1.0f);
	massDist = uniform_real_distribution<float>(0.005f, 0.005f);
	scaleDist = uniform_real_distribution<float>(5.0f, 5.0f);
}

void BulletEmitter::render()
{
	//do nothing
}

void BulletEmitter::update(double tDelta)
{

	//checks if the player is pressing SPACE
	if (Shooting == 1)
	{
		emitCounter += (float)tDelta;

		while(emitCounter >= emitTimeInterval)
		{
			emitCounter -= emitTimeInterval;


			//Assigns the object their attributes 
			float x = position.x;
			float y = position.y;
			float scale = scaleDist(gen);
			float mass = massDist(gen);
			float rotationSpeed = glm::radians(normDist(gen) * 180.0f);
			int spriteIndex = spriteDist(gen);

			//creates the objects
			Bullet* s1 = new Bullet(glm::vec2(x, y), 0.0f, glm::vec2(scale, scale), bullets[spriteIndex], mass, rotationSpeed);

			string key = string("bullet");

			if (particleNumber > 0)
			{
				key += to_string(particleNumber);
			}

			particleNumber++;

			addObject(key.c_str(), s1);
		}
	}
}