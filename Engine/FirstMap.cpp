#include "FirstMap.h"

void FirstMap::DrawMap(Graphics& gfx)
{
	gfx.DrawSprite(0,0,surface.GetWidth(),surface.GetHeight(),surface,Colors::Magenta);
}

std::vector<Obstacle> FirstMap::GetObstacles()
{
	return std::vector<Obstacle>();
}



void FirstMap::InitMap()
{
}
