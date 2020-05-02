#include "Enemy.h"

Enemy::Enemy(Object object, float health, float probability, bool isAlive, int points) :object(object), health(health),
probability(probability), isAlive(isAlive), points(points) {}
