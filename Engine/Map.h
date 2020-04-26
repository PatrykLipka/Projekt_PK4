#pragma once
#include "Obstacle.h"
#include "Crate.h"
#include "vector"

class Map {
	float x;
	float y;
	std::vector<Obstacle> obstacles;
	std::vector<Crate> crates;
public:
	virtual void DrawMap(Graphics& gfx);
	virtual void InitMap();
};