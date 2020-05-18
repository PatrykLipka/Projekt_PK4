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

Round::Round(int numberOfEnemiesInFirstRound) :numberOfEnemiesToSpawn(numberOfEnemiesInFirstRound) {}

std::vector<std::unique_ptr<Enemy>>& Round::GetEnemies() { return enemies; }

void Round::InitRound()
{
	enemies.push_back(std::make_unique<Zombie>(Object(Vec2D(100, 500), Vec2D(1, 1), 23, 41), 100,20,  50, true, 5));
	enemies.push_back(std::make_unique<Zombie>(Object(Vec2D(200, 500), Vec2D(1, 1), 23, 41), 100,20, 50, true, 5));
}

void Round::SpawnEnemy(float dt)
{
	currentTime += dt;
	if (currentTime >= spawnTime&&numberOfEnemiesToSpawn>0) {
		std::random_device device;
		std::mt19937 generator(device());
		std::uniform_int_distribution<int> distribution(1, 4);
		int whichGate = distribution(generator);
		bool findPosition = false;
		float x = 15;
		float y = 325;
		Object obj(Vec2D(x, y), Vec2D(1, 1), 23, 41);
		while (findPosition == false&&whichGate==1) {
			obj = { Vec2D(x,y),Vec2D(1, 1), 23, 41 };
			if (CheckIfSpawnIsPossible(obj)) {
				findPosition = true;
				break;
			}
			y+=22;
			if (y >= 500)break;
		}
		x = 1180;
		y = 325;
		while (findPosition==false && whichGate == 2) {
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
		while ( findPosition == false && whichGate == 3) {
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
		while ( findPosition == false && whichGate == 4) {
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
			numberOfEnemiesToSpawn--;
		}
		else {
			currentTime =spawnTime/4;
		}
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