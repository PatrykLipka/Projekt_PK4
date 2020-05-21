#include "SecondMap.h"

void SecondMap::DrawMap(Graphics& gfx)
{
	gfx.DrawSprite(0, 0, surface.GetWidth(), surface.GetHeight(), surface,Colors::MakeRGB(255,255,255));
}

void SecondMap::InitMap()
{// 248,168 322,443
	Vec2D pos = { 248 + 41,168 + 40 };
	Obstacle ob(Object(pos, Vec2D(0, 0), 82, 79));
	obstacles.push_back(ob);
	Vec2D pos1 = { 254 + 41,366 + 40 };
	Obstacle ob1(Object(pos1, Vec2D(0, 0), 82, 79));
	obstacles.push_back(ob1);
	Vec2D pos2 = { 403 + 41,522 + 40 };
	Obstacle ob2(Object(pos2, Vec2D(0, 0), 82, 79));
	obstacles.push_back(ob2);
	Vec2D pos3 = { 523 + 41,226 + 40 };
	Obstacle ob3(Object(pos3, Vec2D(0, 0), 82, 79));
	obstacles.push_back(ob3);
	Vec2D pos4 = { 735 + 41,256 + 40 };
	Obstacle ob4(Object(pos4, Vec2D(0, 0), 82, 79));
	obstacles.push_back(ob4);
	Vec2D pos5 = { 736 + 41,396 + 40 };
	Obstacle ob5(Object(pos5, Vec2D(0, 0), 82, 79));
	obstacles.push_back(ob5);
	Vec2D pos6 = { 914 + 41,570 + 40 };
	Obstacle ob6(Object(pos6, Vec2D(0, 0), 82, 79));
	obstacles.push_back(ob6);
	Vec2D pos7 = { 997 + 41,104 + 40 };
	Obstacle ob7(Object(pos7, Vec2D(0, 0), 82, 79));
	obstacles.push_back(ob7);
}

std::vector<Obstacle> SecondMap::GetObstacles()
{
	return obstacles;
}

void SecondMap::AddNewBox(float dt)
{
	time += dt;
	if (time >= timeToSpawanBox) {
		std::random_device device;
		std::mt19937 generator(device());
		std::uniform_real_distribution<float> distributionX(13, 1187);
		std::uniform_real_distribution<float> distributionY(13,787 );
		std::uniform_real_distribution<float> timeD(13, 787);
		float x = distributionX(generator);
		float y = distributionX(generator);
		boxes.push_back(Box(Vec2D( x,y ), 13.0f, 13.0f));
		this->time = 0;
		timeToSpawanBox = timeD(generator);
	}
}


