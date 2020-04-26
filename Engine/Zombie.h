#pragma once
#include "Enemy.h"

class Zombie : public Enemy
{
	//Sprite sprite;

public:
	Zombie(Object object, float health, float probability, bool isAlive, int points) :Enemy(object, health, probability, isAlive, points) {};
	void Collision(const Object& object)override;
	void DrawEnemy(Graphics& gtx)override;
	void Shoot()override;
	void ChangeHealth(float changeHP)override;
	bool isDead()override;
	void Movement()override;
};