#pragma once
#include "Map.h"
class SecondMap :
	public Map
{
	float width = 0;
	float height = 0;
	Surface surface = Surface("Images\\Map1.png", 1200, 800);
public:
	void DrawMap(Graphics& gfx)override;
	void InitMap()override;	
	std::vector<Obstacle> GetObstacles()override;
	

	
};

