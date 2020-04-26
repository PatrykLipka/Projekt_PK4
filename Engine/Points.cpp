#include "Points.h"

void Points::IncrementMultiplier()
{
	this->multiplier++;
}

void Points::DecrementMultiplier() 
{
	this->multiplier--;
}

void Points::IncrementPoints(int addedPoints) 
{
	this->points += addedPoints * multiplier;
}