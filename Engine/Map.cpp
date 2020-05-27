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
		std::uniform_real_distribution<float> distributionX(25, 1170);
		std::uniform_real_distribution<float> distributionY(25, 770);
		std::uniform_real_distribution<float> timeD(5,15);
		float x = distributionX(generator);
		float y = distributionY(generator);
		if (CheckIfBoxCanBeSpawn({ x,y }, 13.0f, 13.0f)) {
			boxes.push_back(Box(Vec2D(x, y), 13.0f, 13.0f));
		}
		this->time = 0;
			timeToSpawanBox = timeD(generator);
	}
}
bool Map::CheckIfBoxCanBeSpawn(const Vec2D& vec,float width,float height) {
	Object obj(vec, { 0.0,0.0 },width,height);
	for (auto obs : obstacles) {
		if (obs.getObject().hitbox.IsOverLapping(obj.hitbox)) { return false; }
	}
	return true;
}
std::vector<Box>& Map::GetBox()
{
	return boxes;
}
