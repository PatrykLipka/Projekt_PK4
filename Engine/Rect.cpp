#include "Rect.h"

float Rect::GetWidth()
{
	return right - left;
}

float Rect::GetHeight()
{
	return bottom - top;
}

Rect::Rect(float left_in, float right_in, float top_in, float bottom_in)
	:
	left(left_in),
	right(right_in),
	top(top_in),
	bottom(bottom_in) {}
