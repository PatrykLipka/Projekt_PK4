#pragma once
#include <vector>
#include <string.h>
#include <string>
#include "Surface.h"
#include "Vec2D.h"
#include "Graphics.h"
#include "Rect.h"
class Animation
{
public:
	Animation(int x, int y, int width, int height, int count, const Surface& sprite, float holdTime);
	void Draw(const Vec2D& pos, Graphics& gfx)const;
	void Draw(const Vec2D& pos, Graphics& gfx, const Rect& clip)const;
	void Update(float dt);
	void Advance();
	const Surface& sprite;
	std::vector<Rect>frames;
	int iCurFrame = 0;
	float holdTime;
	float curFrameTime = 0.0f;
	 
};

