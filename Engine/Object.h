#pragma once
#pragma once
#include "Vec2D.h"
#include "Graphics.h"
#include <assert.h>
class Object
{
	class HitBox {
	public:
		float right;
		float left;
		float top;
		float bottom;
		HitBox(float right, float left, float top, float bottom);
		HitBox(const HitBox& box);
		HitBox() = delete;
		bool IsOverLapping(const  HitBox& other);
		void DoActualization(const Vec2D& pos, float width, float height);
		bool IsOverLappingForEnemies(const Vec2D& other);
		bool IsInHitBox(const Vec2D& pos);
		
	};
public:
	Vec2D pos;
	Vec2D movement;
	HitBox hitbox;
	float width;
	float height;
	Object(Vec2D pos, Vec2D mov, float width, float height);
	Object(const Object& obj);
	bool Object::IsOverLapping(const Object other, bool aimsRight, bool aimsLeft, bool aimsDown, bool aimsUp);
	bool Object::IsOverLappingEnemy(const Object other);
	void Move(const Vec2D& mov);
};


