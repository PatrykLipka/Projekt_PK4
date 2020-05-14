#pragma once
#include "Enemy.h"

class Zombie : public Enemy
{
	enum class Sequences {
		WalkingDown,
		WalkingUp,
		WalkingRight,
		WalkingLeft,
		StandDown,
		StandUp,
		StandRight,
		StandLeft,
		Count
	};
	Sequences iCurrentSeqence = Sequences::StandDown;
	std::vector<Animation>animations;
	Surface surface = Surface("Zombie.png", 114, 164);
	std::vector<Vec2D> canBeHit;
public:
	//Zombie();
	Zombie(Object object, float health, float probability, bool isAlive, int points);
	void Draw(Graphics& gfx)override;
	void CheckCollisions(std::vector<Obstacle> obstacles, std::vector<Enemy*> enemies)override;
	bool IsOverLappingObject(const Object other) override;
	void DrawEnemy(Graphics & gtx)override;
	void Attack()override;
	void ChangeHealth(float changeHP)override;
	bool IsAlive()override;
	void PreMovement(float dt, const Object& playerObject, std::vector<Obstacle> obstacles, std::vector<Enemy*> enemies);
	void Movement(bool aim_R, bool aim_L, bool aim_U, bool aim_D, float dt,const Object & playerObject, std::vector<Obstacle> obstacles, std::vector<Enemy*> enemies, float dirX, float dirY, float distance)override;
	void Update(float dt)override;
	void CalculateDistance(const Vec2D& pos)override;
	void Hitted(const float& dmg)override;
};