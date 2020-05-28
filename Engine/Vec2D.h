#pragma once
class Vec2D
{
public:
	Vec2D(float x, float y);
	Vec2D(const Vec2D& vec);
	Vec2D& operator =(const Vec2D& vec);
	Vec2D& operator +=(const Vec2D& vec);
	Vec2D& operator -=(const Vec2D& vec);
	Vec2D& operator * (const float & scalar);
	Vec2D& operator * (const int & scalar);
	bool operator ==(const Vec2D& vec) {
		if (vec.x == this->x && vec.y == this->y)return true;
		else return false;
	}
	float x;
	float y;
};

