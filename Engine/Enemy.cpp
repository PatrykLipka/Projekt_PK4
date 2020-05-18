#include "Enemy.h"

Enemy::Enemy(Object object, float health, float damage, float probability, bool isAlive, int points) :object(object), health(health), damage(damage), probability(probability), isAlive(isAlive), points(points) {};

 Object Enemy::GetObjectW()
{
	return object;
}


