#pragma once
#include "Weapon.h"
class Uzi :
	public Weapon
{
	std::vector<Vec2D> possibleShot;

private:

	void calculatePossibleShot(bool aimsRight, bool aimsLeft, bool aimsDown, bool aimsUp, const Vec2D& pos, bool isMoving);
	bool CheckIfObstacleCanBeHitted(Obstacle obstacle);
	bool CheckIfEnemyCanBeHitted(std::unique_ptr<Enemy>& enemy);
	void CleanVector();
	void MakeCalculationoOfShot(const Object& obj, bool aimsRight, bool aimsLeft, bool aimsDown, bool aimsUp);
	void MergeVector(std::vector<std::unique_ptr<Enemy>>& avaliableTarget, std::vector<std::unique_ptr<Enemy>>& enemy);

public:

	Uzi(int neededPoints=50, float damage=30, float rof=1, float distance=220, float spread=1, int ammo=30, float holdTime=0.1f, float holdTimeOfAnimation=0.09f) :Weapon(neededPoints, damage, rof, distance, spread, ammo, holdTime, holdTimeOfAnimation) {}
	bool Shoot(bool aimsRight, bool aimsLeft, bool aimsDown, bool aimsUp, std::vector<std::unique_ptr<Enemy>>& enemies, std::vector<Obstacle>obstacles, const Vec2D& pos, float dt, bool isMoving)override;
	bool DrawShot(Graphics& gfx, float dt)override;
	void AddAmo(int amo)override;
	void Upgrade(int number)override;
};

