#pragma once
#include "Object.h"
#include "Obstacle.h"
#include "Graphics.h"
#include <algorithm>
#include <list>
#include <vector>
#include "Surface.h"
#include "Animation.h"
#include "Obstacle.h"
#include "Points.h"


class Enemy 
{
protected:
	Object object;
	float health;
	float probability;
	float attackRange;
	float damage;
	int attackIterator = 0;
	int value;
	float attackX;
	float attackY;
	bool isAlive=true;
	int points;
	bool aimsRight;
	bool aimsLeft;
	bool aimsDown;
	bool aimsUp;
	bool animationOver = false;
	bool blockedRight=false;
	bool blockedLeft=false;
	bool blockedDown=false;
	bool blockedUp=false;
	Surface surfaceZombie= Surface("Images\\Zombie.png", 224, 164);
	Surface surfaceBomber= Surface("Images\\Bomber.png", 228, 186);
	std::vector<Animation>animation;
protected:
	virtual void CheckCollisions(std::vector<Obstacle> obstacles, std::vector<std::unique_ptr<Enemy>>& enemies) = 0;
	virtual bool IsOverLappingObject(const Object other) = 0;
	virtual void Update(float dt) = 0;
	virtual float CalculateDistanceToEnemy(const Vec2D& pos) = 0;
	virtual Rect GetBoom() = 0;
	virtual float Attack(float distance, float dt) = 0;
	virtual float Attack(float distance, float dt, std::vector<std::unique_ptr<Enemy>>& enemies, int& delay) = 0;
public:
	bool isHitted = false;
	float distance;
public:
	Enemy() = delete;
	Enemy(Object object, float health, float damage, float probability, bool isAlive, int points);
	virtual void ChangeHealth(float changeHP) = 0;
	virtual void Hitted(const float& dmg) = 0;
	virtual void CalculateDistance(const Vec2D & pos)=0;
	virtual bool IsAlive() = 0;
	virtual int PreMovement(float dt, const Object& playerObject, std::vector<Obstacle> obstacles, std::vector<std::unique_ptr<Enemy>>& enemies, int& delay, float& damageToPlayer) = 0;
	virtual void Movement(bool aim_R, bool aim_L, bool aim_U, bool aim_D, float dt, const Object& playerObject, std::vector<Obstacle> obstacles, std::vector<std::unique_ptr<Enemy>>& enemies, float dirX, float dirY, float distance) = 0;
	virtual void Draw(Graphics& gfx) = 0;
	Object GetObjectW();
	virtual bool Boom(Graphics& gfx, float dt) = 0;
	bool IfAnimationOver();
};