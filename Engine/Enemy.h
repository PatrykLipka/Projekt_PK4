#pragma once
#include "Object.h"
#include "Graphics.h"
#include <list>
#include <vector>
#include "Surface.h"
#include "Animation.h"

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
	float distance = 0;
	Enemy(Object object, float health, float probability, bool isAlive, int points);
	virtual void CheckCollisions(std::vector<Object> obstacles) = 0;
	virtual void DrawEnemy(Graphics& gtx) = 0;
	virtual void Shoot() = 0;
	virtual void ChangeHealth(float changeHP) = 0;
	virtual bool isDead() = 0;
	virtual void Movement(bool aim_R, bool aim_L, bool aim_U, bool aim_D, float dt) = 0;
	virtual void Draw(Graphics& gfx) = 0;
	virtual void Update(float dt)=0;
	virtual Object Getobject()const=0;
	virtual void CalculateDistance(const Vec2D& pos) = 0;
};