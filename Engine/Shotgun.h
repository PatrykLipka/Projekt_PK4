#pragma once
#include "Weapon.h"
class Shotgun :
	public Weapon
{
	bool Shoot(bool aimsRight, bool aimsLeft, bool aimsDown, bool aimsUp, std::vector<std::unique_ptr<Enemy>>& enemies, std::vector<Obstacle>obstacles, const Vec2D& pos, float dt);
	bool DrawShot(Graphics& gfx, float dt) ;
	void AddAmo(int amo);
};

