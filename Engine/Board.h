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
	
	//std::list<Weapon> allWeapons;
	//Points points;
	Map *  map;
	Round round;
public:
	Board(int numberOfEnemiesInFirstRound);
	void StartGame();
	void LevelUp(Player player);
	void SpawnEnemies();
	void InitBoard();
	void DrawBoard(Graphics & gfx);
	std::vector<Obstacle> GetObstacles();
	std::vector<std::unique_ptr<Enemy>>& GetEnemies();
	void SpawnEnemies(float dt);
	//std::vector<Enemy*> GetEnemies();

};