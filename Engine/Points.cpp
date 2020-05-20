#include "Points.h"

//void Points::IncrementMultiplier()
//{
//	this->multiplier++;
//}
//
//void Points::DecrementMultiplier() 
//{
//	this->multiplier--;
//}

int Points::GetPoints()
{
	return points;
}

void Points::IncrementPoints(int addedPoints)
{
	points += addedPoints ;
}