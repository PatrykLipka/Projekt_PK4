#pragma once
#include "Points.h"

class Weapon {
	int neededPoints;
	float damage;
	float rof;
	float distance;
	float spread;
	int ammo;
//	Sound sound;
public:
	virtual void Shoot();
	virtual void Upgrade(Points points);
};