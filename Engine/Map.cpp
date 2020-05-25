#include "Map.h"

void Map::DrawMap(Graphics& gfx)
{
}

void Map::InitMap()
{
}

void Map::AddNewBox(float dt)
{
	time += dt;
	if (time >= timeToSpawanBox) {
		std::random_device device;
		std::mt19937 generator(device());
		std::uniform_real_distribution<float> distributionX(13, 1187);
		std::uniform_real_distribution<float> distributionY(13, 787);
		std::uniform_real_distribution<float> timeD(5,15);
		float x = distributionX(generator);
		float y = distributionY(generator);
		boxes.push_back(Box(Vec2D(x, y), 13.0f, 13.0f));
		this->time = 0;
		timeToSpawanBox = timeD(generator);
	}
}

std::vector<Box>& Map::GetBox()
{
	return boxes;
}
