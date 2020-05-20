#pragma once

 class Points 
{
	 static int points;
public:
	static int GetPoints();
	static void IncrementPoints(int addedPoints);
	void IncrementMultiplier();
	void DecrementMultiplier();
	
};
