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
public:
	float distance;
	Enemy(Object object, float health, float probability, bool isAlive, int points);
	virtual void CheckCollisions(std::vector<Obstacle> obstacles) = 0;
	virtual void DrawEnemy(Graphics& gtx) = 0;
	virtual void Attack() = 0;
	virtual void ChangeHealth(float changeHP) = 0;
	virtual bool IsAlive() = 0;
	virtual void Movement(float dt, const Object& playerObject, std::vector<Obstacle> obstacles) = 0;
	virtual void Draw(Graphics& gfx) = 0;
	virtual void Update(float dt) = 0;
	virtual void CalculateDistance(const Vec2D& pos)=0;
	virtual Object Getobject()const = 0;
	virtual void Hitted(const float& dmg) = 0;
};