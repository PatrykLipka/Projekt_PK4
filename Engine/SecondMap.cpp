#include "SecondMap.h"

void SecondMap::DrawMap(Graphics& gfx)
{
	gfx.DrawSprite(0, 0, surface.GetWidth(), surface.GetHeight(), surface,Colors::MakeRGB(255,255,255));
	for (auto box : boxes) {
		Object obj = box.getObject();
		gfx.DrawSprite(obj.hitbox.left, obj.hitbox.top, obj.hitbox.right, obj.hitbox.bottom, Surface("Images\\crate.png", 25, 24), Colors::MakeRGB(255, 0, 128));
	}
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




