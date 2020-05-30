#pragma once
#include "Enemy.h"
#include "Zombie.h"
#include "Bomber.h"
#include "Map.h"
#include <random>

class Round 
{
	int numberOfEnemiesToSpawn;
	int previousNumberOfEnemies;
	int currentRound=1;
	std::vector<std::unique_ptr<Enemy>> enemies;
	float currentTime = 0;
	float spawnTime = 0.6f;
	float timebetweenrounds = 1.0f;
	float currentTimeBR=0.0f;
public:
	Round(int numberOfEnemiesInFirstRound);
	std::vector<std::unique_ptr<Enemy>>& GetEnemies();
	void InitRound();
	void SpawnEnemy(float dt);
	void NextRound(int additionalEnemies, float dt, Graphics& gfx);
	bool CheckIfSpawnIsPossible(const Object& obj);
	int GetCurrentRound();
};