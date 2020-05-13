#include "Obstacle.h"



void Obstacle::CalculateDistance(const Vec2D& pos)
{
	distance = sqrt(pow(object.pos.x - pos.x, 2) + pow(object.pos.y - pos.y, 2));
}

Object Obstacle::getObject()
{
	return object;
}
