#pragma once

#include "Object.h"
#include "Surface.h"
#include "Graphics.h"
class Obstacle {
	
	Object object;
	
	//const Surface & surface= Surface("Map1.png", 1200, 800);
public:
	float distance = 0;
	Obstacle(const Object & obj):object(obj){}
	void DrawObstacle(Graphics& gfx);
	void CalculateDistance(const Vec2D & pos);
	Object getObject();
};