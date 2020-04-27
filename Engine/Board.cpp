#include "Board.h"

Board::Board()
{
	map = new FirstMap();
}
void Board::DrawBoard(Graphics& gfx)
{
	map->DrawMap(gfx);
}


