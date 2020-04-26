#pragma once

class Points 
{
	int points;
	int multiplier;

public:
	void IncrementPoints(int addedPoints);
	void IncrementMultiplier();
	void DecrementMultiplier();
	Points() : points(0), multiplier(1) {};
};