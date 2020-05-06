#pragma once
#include "Weapon.h"
class Glock :
	public Weapon
{
	std::vector<Vec2D> possibleShot;
public:
	Glock(int neededPoints, float damage, float rof, float distance, float spread, int ammo) :Weapon(neededPoints, damage, rof, distance, spread, ammo){}
	void calculatePossibleShot(bool aimsRight, bool aimsLeft, bool aimsDown, bool aimsUp,const Vec2D& pos);
	void Shoot(bool aimsRight, bool aimsLeft, bool aimsDown, bool aimsUp,std::vector<Enemy*> enemy, const Vec2D& pos)override;
	bool CheckIfEnemyCanBeHitted(const Enemy* enemy);
	void CleanVector();
};

