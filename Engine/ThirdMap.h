#pragma once
#include "Map.h"
class ThirdMap :
	public Map
{
	float width = 0;
	float height = 0;
	Surface surface = Surface("Images\\Map2.png", 1200, 800);
public:
	void DrawMap(Graphics& gfx)override;
	void InitMap()override;
	std::vector<Obstacle> GetObstacles()override;

};

