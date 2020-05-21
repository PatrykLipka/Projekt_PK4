#pragma once
#include "Map.h"
class SecondMap :
	public Map
{
	float width = 0;
	float height = 0;
	float timeToSpawanBox;
	float time;
	std::vector<Obstacle> obstacles;
	std::vector<Box> Boxes;
	const Surface& surface = Surface("Map1.png", 1200, 800);
public:
	void DrawMap(Graphics& gfx)override;
	void InitMap()override;	
	std::vector<Obstacle> GetObstacles()override;
	void AddNewBox()override;

	
};

