#pragma once
#include "Points.h"
#include "Round.h"
#include "Weapon.h"
#include "Player.h"
#include "Map.h"
#include <list>

class Board {
	Round round;
	std::list<Weapon> allWeapons;
	Points points;
	Map* map;
public:
	Graphics& gfx;
	void StartGame();
	void LevelUp(Player player);
	void SpawnEnemies();
	void InitBoard();
};