#pragma once
#include "Weapon.h"

class Shotgun :
	public Weapon
{
	std::vector<std::vector<Vec2D>> possibleShot;
private:

	void calculatePossibleShot(bool aimsRight, bool aimsLeft, bool aimsDown, bool aimsUp, const Vec2D& pos, bool isMoving);
	bool CheckIfObstacleCanBeHitted(Obstacle obstacle, std::vector<Vec2D>& vec);
	bool CheckIfEnemyCanBeHitted(std::unique_ptr<Enemy>& enemy, std::vector<Vec2D>& vec);
	void CleanVector();
	void MakeCalculationoOfShot(const Object& obj, bool aimsRight, bool aimsLeft, bool aimsDown, bool aimsUp, std::vector<Vec2D>& vec);
	void MergeVector(std::vector<std::unique_ptr<Enemy>>& avaliableTarget, std::vector<std::unique_ptr<Enemy>>& enemy);
	void RemoveEnemiesFromVector(std::vector<std::unique_ptr<Enemy>>& enemies);

public:
	Shotgun(int neededPoints = 50, float damage = 20, float rof = 1, float distance = 250, float spread = 0.25f, int ammo = 10, float holdTime = 0.7f, float holdTimeOfAnimation = 0.09f);
	void AddAmo(int amo)override;
	bool Shoot(bool aimsRight, bool aimsLeft, bool aimsDown, bool aimsUp, std::vector<std::unique_ptr<Enemy>>& enemies, std::vector<Obstacle>obstacles, const Vec2D& pos, float dt,bool isMoving)override;
	bool DrawShot(Graphics& gfx, float dt)override;
	
	void Upgrade(int number)override;
};

