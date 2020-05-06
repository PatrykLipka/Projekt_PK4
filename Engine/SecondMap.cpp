#include "SecondMap.h"

void SecondMap::DrawMap(Graphics& gfx)
{
	gfx.DrawSprite(0, 0, surface.GetWidth(), surface.GetHeight(), surface);
}

void SecondMap::InitMap()
{// 248,168
	Vec2D pos = { 248 + 41,168 + 40 };
	Obstacle ob(Object(pos, Vec2D(0, 0), 82, 79));
	obstacles.push_back(ob);
}

std::vector<Obstacle> SecondMap::GetObstacles()
{
	return obstacles;
}
