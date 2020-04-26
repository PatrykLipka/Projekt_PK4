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
	virtual void Collision(const Object& object);
	virtual void DrawEnemy(Graphics& gtx);
	virtual void Shoot();
	virtual void ChangeHealth(float changeHP);
	virtual bool isDead();
	//virtual Enemy(object, health);
	virtual void Movement();
};