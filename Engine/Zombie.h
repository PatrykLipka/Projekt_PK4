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
		AttackDown,
		AttackUp,
		AttackRight,
		AttackLeft,
		Count
	};
	Sequences iCurrentSeqence = Sequences::StandDown;
	std::vector<Animation>animations;
	Surface surface = Surface("Zombie.png", 224, 164);
	std::vector<Vec2D> canBeHit;
	bool Boom(Graphics& gfx, float dt)override;
public:
	//Zombie(); //trzeba dodaæ taki, co bêdzie ustawiaæ od razu probability i isAlive oraz ile jest za nie punktów, bo to siê nie bêdzie zmieniaæ
	Zombie(Object object, float health,float damage, float probability, bool isAlive, int points);
	void Draw(Graphics& gfx)override;
	void CheckCollisions(std::vector<Obstacle> obstacles, std::vector<std::unique_ptr<Enemy>>& enemies)override;
	bool IsOverLappingObject(const Object other) override;
	void DrawEnemy(Graphics & gtx)override;
	float Attack(float distance, float dt)override;
	void ChangeHealth(float changeHP)override;
	bool IsAlive()override;
	int PreMovement(float dt, const Object& playerObject, std::vector<Obstacle> obstacles, std::vector<std::unique_ptr<Enemy>>& enemies, int& delay, float& damageToPlayer) override;
	void Movement(bool aim_R, bool aim_L, bool aim_U, bool aim_D, float dt,const Object & playerObject, std::vector<Obstacle> obstacles, std::vector<std::unique_ptr<Enemy>>& enemies, float dirX, float dirY, float distance)override;
	void Update(float dt)override;
	void CalculateDistance(const Vec2D& pos)override;
	void Hitted(const float& dmg)override;
	float Attack(float distance, float dt, std::vector<std::unique_ptr<Enemy>>& enemies, int& delay) override;
	float CalculateDistanceToEnemy(const Vec2D& pos) override;
	Rect GetBoom()override;
};