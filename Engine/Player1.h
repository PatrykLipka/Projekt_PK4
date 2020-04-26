#pragma once
#include "Animation.h"
#include "Player.h"
#include "Object.h"
class Player1: public Player
{
	//const std::string& path, unsigned int widthOfMianSurface, unsigned int heightOfMianSurface, int widthOfSingleSurface, int heightOfSingleSurface, int amountofsurfaces,
	//int holdTime, int interruptionsW, int interruptionsH, int amountofsequence
//	Animation animation = Animation("Chlopek.png", 130, 155, 20, 32, 5, 20, 9, 9, 4);
	public:
	Player1(Object obj, float hel, bool isAlive) :Player(obj,  hel,  isAlive){}
};

