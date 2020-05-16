#pragma once
#include "Enemy.h"
#include "Zombie.h"
#include "Map.h"
#include <random>

class Round 
{
	int numberOfEnemiesToSpawn;
	int currentRound=1;
	std::vector<std::unique_ptr<Enemy>> enemies;
	float currentTime = 0;
	float spawnTime = 3.0f;
public:
	Round(int numberOfEnemiesInFirstRound);
	std::vector<std::unique_ptr<Enemy>>& GetEnemies();
	void InitRound();
	void SpawnEnemy(float dt);
	void NextRound();
	bool CheckIfSpawnIsPossible(const Object& obj);
};