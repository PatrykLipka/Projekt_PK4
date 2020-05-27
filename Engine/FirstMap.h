#pragma once
#include "Map.h"
#include "Graphics.h"
class FirstMap :
	public Map
{
	float width = 0;
	float height = 0;
public:
	const Surface& surface = Surface("Images\\FirstMap.png", 1200, 800);
	void DrawMap(Graphics& gfx)override;
	std::vector<Obstacle> GetObstacles();
	virtual void InitMap();
};

