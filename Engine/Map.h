#pragma once
#include "Obstacle.h"
#include "Enemy.h"
#include "Crate.h"
#include "vector"
#include "Surface.h"
#include "Graphics.h"
#include "Box.h"

class Map {	
public:
	virtual void DrawMap(Graphics& gfx)=0;
	virtual void InitMap()=0;
	virtual std::vector<Obstacle> GetObstacles() = 0;
	virtual void AddNewBox() = 0;
	//virtual std::vector<Enemy*> GetEnemies() = 0;
};

