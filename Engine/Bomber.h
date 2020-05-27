#pragma once
#include "Enemy.h"

class Bomber : public Enemy
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
	Surface surface = Surface("Images\\Bomber.png", 228, 186);
	std::vector<Vec2D> canBeHit;
	
public:
	float currenttime = 0;
	float holdTime=0.5f;
	//Bomber(); //trzeba dodaæ taki, co bêdzie ustawiaæ od razu probability i isAlive oraz ile jest za nie punktów, bo to siê nie bêdzie zmieniaæ
	Bomber(Object object, float health, float damage, float probability, bool isAlive, int points);
	void Draw(Graphics& gfx)override;
	void CheckCollisions(std::vector<Obstacle> obstacles, std::vector<std::unique_ptr<Enemy>>& enemies)override;
	bool IsOverLappingObject(const Object other) override;
	void DrawEnemy(Graphics& gtx)override;
	virtual float Attack(float distance, float dt) override;
	float Attack(float distance, float dt, std::vector<std::unique_ptr<Enemy>>& enemies, int& delay)override;
	void HitEnemies(std::vector<std::unique_ptr<Enemy>>& enemies, std::vector<std::unique_ptr<Enemy>>& enemiesHit);
	void MergeVector(std::vector<std::unique_ptr<Enemy>>& targets, std::vector<std::unique_ptr<Enemy>>& enemies);
	bool SortByDistance(std::unique_ptr<Enemy>& obj1, std::unique_ptr<Enemy>& obj2);
	void CalculateExplosion(std::vector<std::unique_ptr<Enemy>>& enemies, std::vector<std::unique_ptr<Enemy>>& enemiesHit);
	void ChangeHealth(float changeHP)override;
	bool IsAlive()override;
	int PreMovement(float dt, const Object& playerObject, std::vector<Obstacle> obstacles, std::vector<std::unique_ptr<Enemy>>& enemies, int& delay, float& damageToPlayer) override;
	void Movement(bool aim_R, bool aim_L, bool aim_U, bool aim_D, float dt, const Object& playerObject, std::vector<Obstacle> obstacles, std::vector<std::unique_ptr<Enemy>>& enemies, float dirX, float dirY, float distance)override;
	void Update(float dt)override;
	void CalculateDistance(const Vec2D& pos)override;
	float CalculateDistanceToEnemy(const Vec2D& pos)override;
	void Hitted(const float& dmg)override;
	Rect GetBoom();
	bool Boom(Graphics& gfx,float dt);

};
