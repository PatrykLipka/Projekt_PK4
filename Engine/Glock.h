#pragma once
#include "Weapon.h"
class Glock :
	public Weapon
{
	std::vector<Vec2D> possibleShot;
public:
	Glock(int neededPoints, float damage, float rof, float distance, float spread, int ammo, float holdTime) :Weapon(neededPoints, damage, rof, distance, spread, ammo, holdTime){}
	void calculatePossibleShot(bool aimsRight, bool aimsLeft, bool aimsDown, bool aimsUp,const Vec2D& pos);
	bool Shoot(bool aimsRight, bool aimsLeft, bool aimsDown, bool aimsUp, std::vector<Enemy*> enemy, std::vector<Obstacle>obstacles, const Vec2D& pos, float dt)override;
	void DrawShot(Graphics& gfx, bool aimsRight, bool aimsLeft, bool aimsDown, bool aimsUp, int distance, const Vec2D& pos) override;
	bool CheckIfObstacleCanBeHitted(Obstacle obstacle);
	bool CheckIfEnemyCanBeHitted(Enemy* enemy);
	void CleanVector();
};

