#include "Vec2D.h"

 Vec2D::Vec2D(float x, float y) :x(x), y(y) {}

 Vec2D::Vec2D(const Vec2D& vec) : x(vec.x), y(vec.y) {}

Vec2D& Vec2D::operator=(const Vec2D& vec)
{
	this->x = vec.x;
	this->y = vec.y;
	return *this;
}

Vec2D& Vec2D::operator+=(const Vec2D& vec)
{
	this->x += vec.x;
	this->y += vec.y;
	return *this;
}

Vec2D& Vec2D::operator-=(const Vec2D& vec)
{
	this->x -= vec.x;
	this->y -= vec.y;
	return *this;
}

Vec2D& Vec2D::operator*(const float& scalar)
{
	this->x = this->x * scalar;
	this->y = this->y * scalar;
	return *this;
}

Vec2D& Vec2D::operator*(const int& scalar)
{
	this->x = this->x *(float) scalar;
	this->y = this->y *(float) scalar;
	return *this;
}
