#pragma once
#include "Weapon.h"

class Shotgun :
	public Weapon
{
	std::vector<std::vector<Vec2D>> possibleShot;

	void calculatePossibleShot(bool aimsRight, bool aimsLeft, bool aimsDown, bool aimsUp, const Vec2D& pos);
	bool CheckIfObstacleCanBeHitted(Obstacle obstacle);
	bool CheckIfEnemyCanBeHitted(std::unique_ptr<Enemy>& enemy);
	void CleanVector();
	void MakeCalculationoOfShot(const Object& obj, bool aimsRight, bool aimsLeft, bool aimsDown, bool aimsUp);
	void MergeVector(std::vector<std::unique_ptr<Enemy>>& avaliableTarget, std::vector<std::unique_ptr<Enemy>>& enemy);
public:
	Shotgun(int neededPoints = 50, float damage = 20, float rof = 1, float distance = 250, float spread = 0.5, int ammo = 100, float holdTime = 0.7f, float holdTimeOfAnimation = 0.2f);
	void AddAmo(int amo)override;
	bool Shoot(bool aimsRight, bool aimsLeft, bool aimsDown, bool aimsUp, std::vector<std::unique_ptr<Enemy>>& enemies, std::vector<Obstacle>obstacles, const Vec2D& pos, float dt)override;
	bool DrawShot(Graphics& gfx, float dt)override;
};

