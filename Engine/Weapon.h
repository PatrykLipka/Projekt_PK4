#pragma once
#include "Points.h"
#include "Enemy.h"
#include "Zombie.h"
#include "Vec2D.h"
#include "Graphics.h"
#include <algorithm>    
#include <vector>
#include "FrameTimer.h"

class Weapon {
protected:
	int neededPoints;
	float damage;
	float rof;
	float distance;
	float spread;
	int ammo;
	float holdTime;
	float currentTime = 0;
	//Sound sound;
public:
	Weapon(int neededPoints, float damage, float rof, float distance, float spread, int ammo,float holdTime);
	virtual bool Shoot(bool aimsRight, bool aimsLeft, bool aimsDown, bool aimsUp, std::vector<Enemy*> enemy, std::vector<Obstacle>obstacles, const Vec2D& pos, float dt)=0;

};