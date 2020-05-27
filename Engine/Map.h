#pragma once
#include <random>
#include "Obstacle.h"
#include "Enemy.h"
#include "vector"
#include "Surface.h"
#include "Graphics.h"
#include "Box.h"

class Map {	
protected:
	float timeToSpawanBox=8.0f;
	float time=0;
	std::vector<Obstacle> obstacles;
	std::vector<Box> boxes;
public:
	virtual void DrawMap(Graphics& gfx)=0;
	virtual void InitMap()=0;
	virtual std::vector<Obstacle> GetObstacles() = 0;
	void AddNewBox(float dt);
	std::vector<Box>& GetBox();
	bool CheckIfBoxCanBeSpawn(const Vec2D& vec, float width, float height);
	//virtual std::vector<Enemy*> GetEnemies() = 0;
};

  