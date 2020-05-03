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
	Surface surface = Surface("Zombie.png", 160, 192);
	std::vector<Vec2D> canBeHit;
	

public:
	Zombie();
	Zombie(Object object, float health, float probability, bool isAlive, int points);;
	void Draw(Graphics& gfx)override;
	void CheckCollisions(std::vector<Object> obstacles)override;
	void DrawEnemy(Graphics& gtx)override;
	void Attack()override;
	void ChangeHealth(float changeHP)override;
	bool isDead()override;
	void Movement(float dt, const Object& playerObject)override;
	void Update(float dt)override;
	Object Getobject()const override;
	void CalculateDistance(const Vec2D& pos)override;
};