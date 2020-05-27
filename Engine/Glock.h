#pragma once
#include "Weapon.h"
class Glock :
	public Weapon
{
	//Sound glock_shooting;   /*L"Sounds\\glock_shooting.wav"*/
	std::vector<Vec2D> possibleShot;
public:
	Glock(int neededPoints = 20, float damage = 30, float rof = 1, float distance = 200, float spread = 1, int ammo = std::numeric_limits<int>::infinity(), float holdTime = 0.7f, float holdTimeOfAnimation = 0.2f) :Weapon(neededPoints, damage, rof, distance, spread, ammo, holdTime, holdTimeOfAnimation) {}
	void calculatePossibleShot(bool aimsRight, bool aimsLeft, bool aimsDown, bool aimsUp,const Vec2D& pos);
	bool Shoot(bool aimsRight, bool aimsLeft, bool aimsDown, bool aimsUp, std::vector<std::unique_ptr<Enemy>>& enemies, std::vector<Obstacle>obstacles, const Vec2D& pos, float dt)override;
	bool DrawShot(Graphics& gfx, float dt)override;
	bool CheckIfObstacleCanBeHitted(Obstacle obstacle);
	bool CheckIfEnemyCanBeHitted(std::unique_ptr<Enemy>& enemy);
	void CleanVector();
	void MakeCalculationoOfShot(const Object& obj, bool aimsRight, bool aimsLeft, bool aimsDown, bool aimsUp);
	void MergeVector(std::vector<std::unique_ptr<Enemy>>& avaliableTarget, std::vector<std::unique_ptr<Enemy>>& enemy);
	void AddAmo(int amo)override;
};

