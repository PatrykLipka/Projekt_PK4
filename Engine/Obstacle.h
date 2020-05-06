#pragma once

#include "Object.h"
#include "Surface.h"
#include "Graphics.h"
class Obstacle {
	Object object;
	//const Surface & surface= Surface("Map1.png", 1200, 800);
public:
	Obstacle(const Object & obj):object(obj){}
	void DrawObstacle(Graphics& gfx);
	Object getObject();

};