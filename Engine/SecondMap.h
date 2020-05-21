#pragma once
#include "Map.h"
class SecondMap :
	public Map
{
	float width = 0;
	float height = 0;
	std::vector<Obstacle> obstacles;
	std::vector<Box> boxes;
	const Surface& surface = Surface("Map1.png", 1200, 800);
public:
	void DrawMap(Graphics& gfx)override;
	void InitMap()override;	
	std::vector<Obstacle> GetObstacles()override;
	void AddNewBox(float dt)override;

	
};

