#pragma once
#include "Points.h"
#include "Round.h"
#include "Weapon.h"
#include "Player.h"
#include "Map.h"
#include "FirstMap.h"
#include "SecondMap.h"
#include "Obstacle.h"
#include <list>

class Board {
	//Round round;
	//std::list<Weapon> allWeapons;
	//Points points;
	Map *  map;
public:
	Board();
	void StartGame();
	void LevelUp(Player player);
	void SpawnEnemies();
	void InitBoard();
	void DrawBoard(Graphics & gfx);
	std::vector<Obstacle> GetObstacles();
	//std::vector<Enemy*> GetEnemies();

};