#pragma once
#include "Enemy.h"

class Bomber : public Enemy
{
private:

	enum class Sequences {
		WalkingDown,
		WalkingUp,
		WalkingRight,
		WalkingLeft,
		StandDown,
		StandUp,
		StandRight,
		StandLeft,
		AttackDown,
		AttackUp,
		AttackRight,
		AttackLeft,
		Count
	};

	Sequences iCurrentSeqence = Sequences::StandDown;
	Surface& surface = surfaceBomber;
	std::vector<Animation>& animations = animation;
	float currenttime = 0;
	float holdTime=0.5f;
private:
	void CheckCollisions(std::vector<Obstacle> obstacles, std::vector<std::unique_ptr<Enemy>>& enemies)override;
	bool IsOverLappingObject(const Object other) override;
	void HitEnemies(std::vector<std::unique_ptr<Enemy>>& enemies, std::vector<std::unique_ptr<Enemy>>& enemiesHit);
	void MergeVector(std::vector<std::unique_ptr<Enemy>>& targets, std::vector<std::unique_ptr<Enemy>>& enemies);
	bool SortByDistance(std::unique_ptr<Enemy>& obj1, std::unique_ptr<Enemy>& obj2);
	void CalculateExplosion(std::vector<std::unique_ptr<Enemy>>& enemies, std::vector<std::unique_ptr<Enemy>>& enemiesHit);
	void Update(float dt)override;
	void CalculateDistance(const Vec2D& pos)override;
	float CalculateDistanceToEnemy(const Vec2D& pos)override;
	Rect GetBoom();
public:
	Bomber(Object object, float health, float damage, float probability, bool isAlive, int points);
	Bomber() = delete;
	void Draw(Graphics& gfx)override;
	float Attack(float distance, float dt) override;
	float Attack(float distance, float dt, std::vector<std::unique_ptr<Enemy>>& enemies, int& delay)override;
	void ChangeHealth(float changeHP)override;
	bool IsAlive()override;
	int PreMovement(float dt, const Object& playerObject, std::vector<Obstacle> obstacles, std::vector<std::unique_ptr<Enemy>>& enemies, int& delay, float& damageToPlayer) override;
	void Movement(bool aim_R, bool aim_L, bool aim_U, bool aim_D, float dt, const Object& playerObject, std::vector<Obstacle> obstacles, std::vector<std::unique_ptr<Enemy>>& enemies, float dirX, float dirY, float distance)override;
	void Hitted(const float& dmg)override;
	bool Boom(Graphics& gfx,float dt);

};
