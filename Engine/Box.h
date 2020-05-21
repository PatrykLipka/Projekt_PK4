#pragma once
#include <random>
#include "Object.h"
#include "Player.h"
class Box
{
	Object object;
	//Surface
	bool alreadyColected = false;
public:
	Box(Object& obj) :object(obj) {}
	Box(Vec2D& pos, float width, float height) :object(pos, { 0,0 }, width, height) {};
	Box() = delete;
	bool IsBoxCollected(const Object& player);
	void ColectBox(Player & player);
	bool AlreadyColected();
};

