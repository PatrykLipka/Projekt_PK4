#pragma once
#include "Vec2D.h"
class Rect
{ public:
	float left;
	float right;
	float top;
	float bottom;
	float GetWidth();
	float GetHeight();
	Rect(float left_in, float right_in, float top_in, float bottom_in);
	Rect(const Vec2D & topLeft, const Vec2D  & bottomRight)
		:
		Rect(topLeft.x, bottomRight.x, topLeft.y, bottomRight.y)
	{}
};

