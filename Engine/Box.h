#pragma once
#include <random>
#include "Object.h"
#include "Player.h"
class Box
{
	Object object;
	//Surface
	bool alreadyColected ;
public:
	Box(Object& obj);
	Box(Vec2D& pos, float width, float height);
	bool IsBoxCollected(const Object& player);
	void ColectBox(Player & player);
	bool AlreadyColected();
	Object getObject();
};

