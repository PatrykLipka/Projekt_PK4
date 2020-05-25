#include "Round.h"
//
//Round::NextRound() 
//{
//	numberOfEnemies += 4;
//	currentRound++;
//	for (int i = 0; i < numberOfEnemies; i++) 
//	{
//		//tutaj trzeba zrobiæ tworzenie przeciwników
//	}
//}

Round::Round(int numberOfEnemiesInFirstRound) :numberOfEnemiesToSpawn(numberOfEnemiesInFirstRound),previousNumberOfEnemies(numberOfEnemiesInFirstRound) {}

std::vector<std::unique_ptr<Enemy>>& Round::GetEnemies() { return enemies; }

void Round::InitRound()
{
	
}

void Round::SpawnEnemy(float dt)
{
	currentTime += dt;
	if (currentTime >= spawnTime && numberOfEnemiesToSpawn > 0) {
		std::random_device device;
		std::mt19937 generator(device());
		std::uniform_int_distribution<int> distribution(1, 4);
		std::uniform_int_distribution<int> propabilityforspawn(1, 100);
		int whichGate = distribution(generator);
		int whichTypeOfEnemy = propabilityforspawn(generator);
		bool findPosition = false;
		
		if (whichTypeOfEnemy < 75) {
		float x = 15;
		float y = 325;
			Object obj(Vec2D(x, y), Vec2D(1, 1), 23, 41);
			while (findPosition == false && whichGate == 1) {
				obj = { Vec2D(x,y),Vec2D(1, 1), 23, 41 };
				if (CheckIfSpawnIsPossible(obj)) {
					findPosition = true;
					break;
				}
				y += 22;
				if (y >= 500)break;
			}
			x = 1180;
			y = 325;
			while (findPosition == false && whichGate == 2) {
				obj = { Vec2D(x,y),Vec2D(1, 1), 23, 41 };
				if (CheckIfSpawnIsPossible(obj)) {
					findPosition = true;
					break;
				}
				y += 22;
				if (y >= 500)break;
			}
			x = 500;
			y = 25;
			while (findPosition == false && whichGate == 3) {
				obj = { Vec2D(x,y),Vec2D(1, 1), 23, 41 };
				if (CheckIfSpawnIsPossible(obj)) {
					findPosition = true;
					break;
				}
				x += 12;
				if (x >= 700)break;
			}
			x = 500;
			y = 780;
			while (findPosition == false && whichGate == 4) {
				obj = { Vec2D(x,y),Vec2D(1, 1), 23, 41 };
				if (CheckIfSpawnIsPossible(obj)) {
					findPosition = true;
					break;
				}
				x += 12;
				if (x >= 700)break;
			}
			if (findPosition == true) {
				enemies.push_back(std::make_unique<Zombie>(obj, 100, 20, 50, true, 5));
				currentTime = 0;
				--numberOfEnemiesToSpawn;
			}
			else {
				currentTime = spawnTime / 4;
			}
		}
		else {
			float x = 15;
			float y = 325;
			Object obj(Vec2D(x, y), Vec2D(1, 1), 23, 46);
			while (findPosition == false && whichGate == 1) {
				obj = { Vec2D(x,y),Vec2D(1, 1), 23, 46 };
				if (CheckIfSpawnIsPossible(obj)) {
					findPosition = true;
					break;
				}
				y += 23;
				if (y >= 500)break;
			}
			x = 1180;
			y = 325;
			while (findPosition == false && whichGate == 2) {
				obj = { Vec2D(x,y),Vec2D(1, 1), 23, 46 };
				if (CheckIfSpawnIsPossible(obj)) {
					findPosition = true;
					break;
				}
				y += 23;
				if (y >= 500)break;
			}
			x = 500;
			y = 25;
			while (findPosition == false && whichGate == 3) {
				obj = { Vec2D(x,y),Vec2D(1, 1), 23, 46 };
				if (CheckIfSpawnIsPossible(obj)) {
					findPosition = true;
					break;
				}
				x += 13;
				if (x >= 700)break;
			}
			x = 500;
			y = 780;
			while (findPosition == false && whichGate == 4) {
				obj = { Vec2D(x,y),Vec2D(1, 1), 23, 46 };
				if (CheckIfSpawnIsPossible(obj)) {
					findPosition = true;
					break;
				}
				x += 13;
				if (x >= 700)break;
			}
			if (findPosition == true) {
				enemies.push_back(std::make_unique<Bomber>(obj, 80, 40, 50, true, 5));
				currentTime = 0;
				numberOfEnemiesToSpawn = numberOfEnemiesToSpawn - 1;
			}

			else {
				currentTime = spawnTime / 4;
			}
		}
	}
}

		

void Round::NextRound(int additionalEnemies)
{
	if (enemies.size()==0) {
		numberOfEnemiesToSpawn = additionalEnemies + previousNumberOfEnemies;
		previousNumberOfEnemies = numberOfEnemiesToSpawn;
		currentRound++;
	}
}
bool Round::CheckIfSpawnIsPossible(const Object& obj)
{
	for (auto& e : enemies) {
		if (!e->GetObjectW().hitbox.IsOverLapping(obj.hitbox)) {}
		else { return false; }
	}
	return true;
}