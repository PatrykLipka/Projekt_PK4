#include "FirstMap.h"

void FirstMap::DrawMap(Graphics& gfx)
{
	gfx.DrawSprite(0,0,surface.GetWidth(),surface.GetHeight(),surface);
}

void FirstMap::InitMap()
{
}
