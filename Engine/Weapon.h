#pragma once
#include "Points.h"
#include "Enemy.h"
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
	virtual void Shoot(bool aimsRight, bool aimsLeft, bool aimsDown, bool aimsUp,std::vector<Enemy*> enemy, const Vec2D& pos)=0;
	//virtual void Upgrade(Points points);
	Weapon(int neededPoints, float damage, float rof, float distance, float spread, int ammo);
};