#pragma once

 class Points 
{
	static int points;
	int multiplier;

public:
	static void IncrementPoints(int addedPoints);
	void IncrementMultiplier();
	void DecrementMultiplier();
	Points() : multiplier(1) { points = 0; };
};