#pragma once
#include "Enemy.h"

class Round 
{
	static int numberOfEnemies;
	int currentRound;
	/*Enemy* enemies = new Enemy[numberOfEnemies];*/

public:
	void NextRound();
};