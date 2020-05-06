#include "Board.h"

Board::Board()
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




