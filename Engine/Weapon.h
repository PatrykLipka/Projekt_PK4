#pragma once
#include "Points.h"
#include "Enemy.h"
#include "Zombie.h"
#include "Vec2D.h"
#include "Graphics.h"
#include <algorithm>    
#include <vector>

class Weapon {
protected:
	int neededPoints;
	float damage;
	float rof;
	float distance;
	float spread;
	int ammo;
	//Sound sound;
public:
	Weapon(int neededPoints, float damage, float rof, float distance, float spread, int ammo);
	virtual int Shoot(bool aimsRight, bool aimsLeft, bool aimsDown, bool aimsUp,std::vector<Enemy*> enemy, const Vec2D& pos)=0;
};