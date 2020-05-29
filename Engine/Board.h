#pragma once
#include "Points.h"
#include "Round.h"
#include "Weapon.h"
#include "Player.h"
#include "Map.h"
#include "FirstMap.h"
#include "SecondMap.h"
#include "Obstacle.h"
#include <algorithm>


class Board {
	
	std::vector<std::shared_ptr<Weapon>> allWeapons;
	Map *  map;
	Round round;
	void InitVectorOfWeapon();
public:
	Board(int numberOfEnemiesInFirstRound);
	void StartGame();
	void LevelUp(Player & player);
	void SpawnEnemies();
	void InitBoard();
	void DrawBoard(Graphics & gfx);
	std::vector<Obstacle> GetObstacles();
	std::vector<std::unique_ptr<Enemy>>& GetEnemies();
	std::vector<Box> GetBoxes();
	void SpawnEnemies(float dt);
	void NextRound(float dt, Graphics& gfx);
	std::shared_ptr<Weapon>& GetAvaliableGun();
	void AddNewBox(float dt);
	void ColectBox(Player& player);
	
	//std::vector<Enemy*> GetEnemies();

};