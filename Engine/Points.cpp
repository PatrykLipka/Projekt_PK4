#include "Points.h"

int Points::GetPoints()
{
	return points;
}

void Points::IncrementPoints(int addedPoints)
{
	points += addedPoints ;
}