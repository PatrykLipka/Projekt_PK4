#pragma once
#include "Object.h"
#include "Obstacle.h"
#include "Graphics.h"
#include <list>
#include <vector>
#include "Surface.h"
#include "Animation.h"
#include "Obstacle.h"


class Enemy 
{
protected:
	Object object;
	float health;
	float probability;
	bool isAlive;
	int points;
	bool aimsRight;
	bool aimsLeft;
	bool aimsDown;
	bool aimsUp;

	bool blockedRight=false;
	bool blockedLeft=false;
	bool blockedDown=false;
	bool blockedUp=false;
	

public:
	bool isHitted = false;
	float distance;
	Enemy(Object object, float health, float probability, bool isAlive, int points);
	virtual void CheckCollisions(std::vector<Obstacle> obstacles, std::vector<Enemy*> enemies) = 0;
	virtual bool IsOverLappingObject(const Object other) = 0;
	virtual void DrawEnemy(Graphics& gtx) = 0;
	virtual void Attack() = 0;
	virtual void ChangeHealth(float changeHP) = 0;
	virtual bool IsAlive() = 0;
	virtual void PreMovement(float dt, const Object& playerObject, std::vector<Obstacle> obstacles, std::vector<Enemy*> enemies) = 0;
	virtual void Movement(bool aim_R, bool aim_L, bool aim_U, bool aim_D, float dt, const Object& playerObject, std::vector<Obstacle> obstacles, std::vector<Enemy*> enemies, float dirX, float dirY, float distance) = 0;
	virtual void Draw(Graphics& gfx) = 0;
	virtual void Update(float dt) = 0;
	virtual void CalculateDistance(const Vec2D& pos)=0;
	Object GetObjectW()
	{
		return object;
	}
	virtual void Hitted(const float& dmg) = 0;
};