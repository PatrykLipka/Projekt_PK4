#pragma once
#include "Map.h"
#include "Graphics.h"
class FirstMap : public Map
{	const Surface& surface = Surface("Images\\FirstMap.png", 1200, 800);
	float width = 0;
	float height = 0;
public:
	void DrawMap(Graphics& gfx)override;
	std::vector<Obstacle> GetObstacles()override;
	void InitMap()override;
};

