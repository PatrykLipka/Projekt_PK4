#pragma once
#include "Graphics.h"
#include "Object.h"

class Enemy {
	Object object;
	float health;
	float probability;
	bool isAlive;
	int points;

public:
	Enemy(Object object, float health, float probability, bool isAlive, int points) :object(object), health(health),
		probability(probability), isAlive(isAlive), points(points) {};
	virtual void Collision(const Object& object) = 0;
	virtual void DrawEnemy(Graphics& gtx) = 0;
	virtual void Shoot() = 0;
	virtual void ChangeHealth(float changeHP) = 0;
	virtual bool isDead() = 0;
	virtual void Movement() = 0;
};