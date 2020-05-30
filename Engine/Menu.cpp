#include "Menu.h"
#include "SecondMap.h"

Menu::Menu()
{
}
//145,230
void Menu::DrawMenu(Graphics& gfx)
{
	gfx.DrawSprite(0, 0, Graphics::ScreenWidth, Graphics::ScreenHeight, menu,Colors::Magenta);
	if(currentMap==1){
		gfx.DrawSprite(145,230,385,390,map1, Colors::Magenta);
	}
	else if (currentMap == 2) {
		gfx.DrawSprite(145, 230, 385, 390, map2, Colors::Magenta);
	}
}

int Menu::Settings(const Vec2D& vec)
{

			if (start.hitbox.IsInHitBox(vec)) {
				gamestart = true;
				if (currentMap == 1)return 1;//std::make_shared<SecondMap>();
				if (currentMap == 2)return 2;//std::make_shared<SecondMap>();

			}
			else if (exit.hitbox.IsInHitBox(vec))return 3;
			else if (left.hitbox.IsInHitBox(vec)) {
				if (currentMap == 1)currentMap = 2;
				else if (currentMap == 2)currentMap = 1;
				//if (currentMap == 3)currentMap = 2;
			}
			else if (right.hitbox.IsInHitBox(vec)) {
				if (currentMap == 1)currentMap = 2;
				else if (currentMap == 2)currentMap = 1;
				//	if (currentMap == 3)currentMap = 1;
			}
		
		
}
