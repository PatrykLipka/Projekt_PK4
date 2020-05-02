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

	Sequences iCurentSeqence = Sequences::StandDown;
	std::vector<Animation>animations;
	Surface surface = Surface("Zombie.png", 160, 192);
	std::vector<Vec2D> canBeHit;
	

public:
	Zombie(Object object, float health, float probability, bool isAlive, int points);;
	void Draw(Graphics& gfx)override;
	void CheckCollisions(std::vector<Object> obstacles)override;
	void DrawEnemy(Graphics& gtx)override;
	void Shoot()override;
	void ChangeHealth(float changeHP)override;
	bool isDead()override;
	void Movement(bool aim_R, bool aim_L, bool aim_U, bool aim_D, float dt)override;
	void Update(float dt)override;
};