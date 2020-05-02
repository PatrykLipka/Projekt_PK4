#pragma once
#include "Weapon.h"
#include <vector>
#include "Vec2D.h"
class Glock :
	public Weapon
{
	std::vector<Vec2D> possibleShot;
public:
	Glock(int neededPoints, float damage, float rof, float distance, float spread, int ammo) :Weapon(neededPoints, damage, rof, distance, spread, ammo){}
	void calculatePossibleShot(bool aimsRight, bool aimsLeft, bool aimsDown, bool aimsUp);
};

