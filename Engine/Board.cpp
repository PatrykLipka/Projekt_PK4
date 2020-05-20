#include "Board.h"

Board::Board(int numberOfEnemiesInFirstRound):round(numberOfEnemiesInFirstRound)
{
	map = new SecondMap();
	InitVectorOfWeapon();
}
void Board::LevelUp(Player& player)
{
	if (Points::GetPoints() >= 0) {
       		if (allWeapons.size()==1&& typeid(*allWeapons[0]) == typeid(Uzi)) {
  			player.SetNewOwnedGun(allWeapons[0]);
			allWeapons.erase(std::remove_if(allWeapons.begin(), allWeapons.end(), [](std::shared_ptr<Weapon> e) {if (typeid(*e) == typeid(Uzi))return true; else return false; }), allWeapons.end());
		}
	}
}
void Board::InitBoard()
{
	map->InitMap();
}
void Board::DrawBoard(Graphics& gfx)
{
	map->DrawMap(gfx);
}

std::vector<Obstacle> Board::GetObstacles()
{
	return map->GetObstacles();
}
std::vector<std::unique_ptr<Enemy>>& Board::GetEnemies()
{
	return round.GetEnemies();
}

void Board::SpawnEnemies(float dt)
{
	round.SpawnEnemy(dt);
	
}

void Board::NextRound()
{
	round.NextRound(2);
}

void Board::InitVectorOfWeapon()
{
	allWeapons.push_back(std::make_shared <Uzi>());
}


//std::vector<Enemy*> Board::GetEnemies()
//{
//	return map->GetEnemies();
//}


