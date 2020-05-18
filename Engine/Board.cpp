#include "Board.h"

Board::Board(int numberOfEnemiesInFirstRound):round(numberOfEnemiesInFirstRound)
{
	map = new SecondMap();
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


//std::vector<Enemy*> Board::GetEnemies()
//{
//	return map->GetEnemies();
//}


