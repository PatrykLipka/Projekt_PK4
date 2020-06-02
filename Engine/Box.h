#pragma once
#include <random>
#include "Object.h"
#include "Player.h"

class Box
{
	Object object;
	bool alreadyColected ;
private:
	bool IsBoxCollected(const Object& player);
public:
	Box() = delete;
	Box(Object& obj);
	Box(Vec2D& pos, float width, float height);
	void ColectBox(Player & player);
	bool AlreadyColected();
	Object getObject();
};

