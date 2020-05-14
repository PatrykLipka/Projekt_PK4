#include "Animation.h"

Animation::Animation(int x, int y, int width, int height, int count, const Surface& sprite, float holdTime)
	:sprite(sprite),
	holdTime(holdTime)
	
{
	for (int i = 0; i < count; i++) {
		frames.emplace_back(x + i * width, x + (i + 1) * width, y, y + height);
}
}

void Animation::Draw(const Vec2D& pos, Graphics& gfx) const
{
	gfx.DrawSprite(pos.x, pos.y, frames[iCurFrame], sprite);
}

void Animation::Draw(const Vec2D& pos, Graphics& gfx, const Rect& clip) const
{
}

void Animation::DrawH(const Vec2D& pos, Graphics& gfx) const
{
	gfx.DrawSpriteH(pos.x, pos.y, frames[iCurFrame], sprite);
}

void Animation::Update(float dt)
{
	curFrameTime += dt;
	if (curFrameTime  >= holdTime) {
		Advance();
		curFrameTime -= holdTime;
	}
}

void Animation::Advance()
{
	if (++iCurFrame >= frames.size()) {
		iCurFrame = 0;
	}
}
