#pragma once
class Vec2D
{public:
	Vec2D(float x, float y);
	Vec2D(const Vec2D& vec);
	Vec2D& operator =(const Vec2D& vec);
	Vec2D& operator +=(const Vec2D& vec);
	Vec2D& operator -=(const Vec2D& vec);
	Vec2D& operator * (const float & scalar);
	Vec2D& operator * (const int & scalar);
	float x;
	float y;
};

