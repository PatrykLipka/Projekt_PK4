#pragma once
#include "Points.h"
#include "Enemy.h"
#include "Zombie.h"
#include "Vec2D.h"
#include "Graphics.h"
#include <algorithm>    
#include <vector>
#include "FrameTimer.h"
#include "Sound.h"

class Weapon {
protected:

	int neededPoints;
	float damage;
	float rof;
	float distance;
	float spread;
	int ammo;
	float holdTime;
	float holdTimeOfAnimation;
	float currentTime = 0;
	float currentTimeOfAnimation = 0;

public:

	Weapon(int neededPoints, float damage, float rof, float distance, float spread, int ammo,float holdTime, float holdTimeOfAnimation);
	virtual bool Shoot(bool aimsRight, bool aimsLeft, bool aimsDown, bool aimsUp, std::vector<std::unique_ptr<Enemy>>& enemies, std::vector<Obstacle>obstacles, const Vec2D& pos, float dt, bool isMoving)=0;
	virtual bool DrawShot(Graphics& gfx, float dt) = 0;
	virtual void AddAmo(int amo) = 0;
	std::string GetInformationAboutCurrentGun();
	std::string GetName();
	virtual void Upgrade(int number) = 0;


};