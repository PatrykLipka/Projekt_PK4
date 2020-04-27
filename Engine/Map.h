#pragma once
#include "Obstacle.h"
#include "Crate.h"
#include "vector"
#include "Surface.h"
#include "Graphics.h"

class Map {	
public:
	virtual void DrawMap(Graphics& gfx);
	virtual void InitMap();
	
};

