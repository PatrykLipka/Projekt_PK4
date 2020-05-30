#pragma once
#include "Surface.h"
#include "Map.h"
class Menu
{
	Surface menu = Surface("Images\\Menu.png", 1200, 800);
	Surface map1 = Surface("Images\\Map1_miniature.png", 240, 160);
	Surface map2 = Surface("Images\\Map2_miniature.png", 240, 160);
	int currentMap = 1;
	Object start = Object({ 272,125 }, { 0,0 }, 255, 50);
	Object exit = Object({ 270,497 }, { 0,0 }, 255, 50);
	Object left = Object({ 87.5,295 }, { 0,0 }, 65, 50);
	Object right = Object({457.5 ,295 }, { 0,0 }, 65, 50);
	float time = 0;
	float timeBettwenClick = 0.1f;
public:
	Menu();
	bool gamestart = false;
	void DrawMenu(Graphics& gfx);
	int Settings(const Vec2D& vec,float dt);

};

