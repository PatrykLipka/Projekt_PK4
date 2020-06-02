#pragma once
#include "Enemy.h"
#include "Zombie.h"
#include "Bomber.h"
#include "Map.h"
#include <random>

class Round 
{
private:

	int numberOfEnemiesToSpawn;
	int previousNumberOfEnemies;
	int currentRound=2;
	float currentTime = 0;
	float spawnTime = 1.0f;
	float timebetweenrounds = 2.0f;
	float currentTimeBR=0.0f;

private:

	std::vector<std::unique_ptr<Enemy>> enemies;

private:

	bool CheckIfSpawnIsPossible(const Object& obj);

public:

	Round(int numberOfEnemiesInFirstRound);
	std::vector<std::unique_ptr<Enemy>>& GetEnemies();
	void SpawnEnemy(float dt);
	void NextRound(int additionalEnemies, float dt, Graphics& gfx);
	int GetCurrentRound();
};