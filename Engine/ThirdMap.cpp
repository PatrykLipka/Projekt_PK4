#include "ThirdMap.h"

void ThirdMap::DrawMap(Graphics& gfx)
{
	gfx.DrawSprite(0, 0, surface.GetWidth(), surface.GetHeight(), surface, Colors::MakeRGB(255, 255, 255));
	for (auto box : boxes) {
		Object obj = box.getObject();
		gfx.DrawSprite(obj.hitbox.left, obj.hitbox.top, obj.hitbox.right, obj.hitbox.bottom, Surface("Images\\crate.png", 25, 24), Colors::MakeRGB(255, 0, 128));
	}
}

void ThirdMap::InitMap()
{// 248,168 322,443
	Vec2D pos = { 105 + 41,95 + 40 };
	Obstacle ob(Object(pos, Vec2D(0, 0), 82, 79));
	obstacles.push_back(ob);
	Vec2D pos1 = { 95 + 41,609 + 40 };
	Obstacle ob1(Object(pos1, Vec2D(0, 0), 82, 79));
	obstacles.push_back(ob1);
	Vec2D pos2 = { 345 + 41,477 + 40 };
	Obstacle ob2(Object(pos2, Vec2D(0, 0), 82, 79));
	obstacles.push_back(ob2);
	Vec2D pos3 = { 357 + 41,204 + 40 };
	Obstacle ob3(Object(pos3, Vec2D(0, 0), 82, 79));
	obstacles.push_back(ob3);
	Vec2D pos4 = { 560 + 41,336 + 40 };
	Obstacle ob4(Object(pos4, Vec2D(0, 0), 82, 79));
	obstacles.push_back(ob4);
	Vec2D pos5 = { 773 + 41,212 + 40 };
	Obstacle ob5(Object(pos5, Vec2D(0, 0), 82, 79));
	obstacles.push_back(ob5);
	Vec2D pos6 = { 775 + 41,478 + 40 };
	Obstacle ob6(Object(pos6, Vec2D(0, 0), 82, 79));
	obstacles.push_back(ob6);
	Vec2D pos7 = { 1008 + 41,96 + 40 };
	Obstacle ob7(Object(pos7, Vec2D(0, 0), 82, 79));
	obstacles.push_back(ob7);
	Vec2D pos8= { 1000+ 41,605 + 40 };
	Obstacle ob8(Object(pos8, Vec2D(0, 0), 82, 79));
	obstacles.push_back(ob8);
}

std::vector<Obstacle> ThirdMap::GetObstacles()
{
	return obstacles;
}




