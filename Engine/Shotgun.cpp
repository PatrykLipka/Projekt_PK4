#include "Shotgun.h"

bool Shotgun::Shoot(bool aimsRight, bool aimsLeft, bool aimsDown, bool aimsUp, std::vector<std::unique_ptr<Enemy>>& enemies, std::vector<Obstacle> obstacles, const Vec2D& pos, float dt)
{
	return false;
}

bool Shotgun::DrawShot(Graphics& gfx, float dt)
{
	return false;
}

void Shotgun::AddAmo(int amo)
{
}
