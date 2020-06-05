#pragma once
#include "Surface.h"
#include "Map.h"
class Menu
{
	Surface menu = Surface("Images\\Menu.png", 1200, 800);
	Surface map1 = Surface("Images\\Map1_miniature.png", 240, 160);
	Surface map2 = Surface("Images\\Map2_miniature.png", 240, 160);
	int currentMap = 1;
	Object start = Object({ 599, 186.5f }, { 0,0 }, 285, 80);
	Object exit = Object({ 599, 558 }, { 0,0 }, 286, 80);
	Object left = Object({ 416, 360.5f}, { 0,0 }, 80, 81);
	Object right = Object({ 783, 361.5 }, { 0,0 }, 80, 81);
public:
	Menu();
	bool gamestart = false;
	void DrawMenu(Graphics& gfx);
	int Settings(const Vec2D& vec);

};

