#include "FirstMap.h"

void FirstMap::DrawMap(Graphics& gfx)
{
	gfx.DrawSprite(0,0,surface.GetWidth(),surface.GetHeight(),surface);
}

std::vector<Obstacle> FirstMap::GetObstacles()
{
	return obstacles;
}

void FirstMap::InitMap()
{
}
