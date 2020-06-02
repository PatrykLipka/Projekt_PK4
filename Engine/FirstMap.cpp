#include "FirstMap.h"

void FirstMap::DrawMap(Graphics& gfx)
{
	gfx.DrawSprite(0,0,float(surface.GetWidth()),float(surface.GetHeight()),surface,Colors::Magenta);
	for (auto box : boxes) {
		Object obj = box.getObject();
		gfx.DrawSprite(obj.hitbox.left, obj.hitbox.top, obj.hitbox.right, obj.hitbox.bottom, Surface("Images\\crate.png", 25, 24), Colors::MakeRGB(255, 0, 128));
	}
}

std::vector<Obstacle> FirstMap::GetObstacles()
{
	return std::vector<Obstacle>();
}



void FirstMap::InitMap()
{
}


