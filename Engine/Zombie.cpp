#include "Zombie.h"

#include "Player.h"

void Zombie::Movement(bool aim_R, bool aim_L, bool aim_U, bool aim_D, float dt)
{
	
}

void Zombie::CheckCollisions(std::vector<Object> obstacles)
{
	for (auto obs : obstacles) {
		this->object.IsOverLapping(obs, aimsRight, aimsLeft, aimsDown, aimsUp);
	}
}

void Zombie::Draw(Graphics& gfx)
{
	Vec2D pos{ object.hitbox.right,object.hitbox.top };
	animations[(int)iCurentSeqence].Draw(pos, gfx);
}

void Zombie::Update(float dt)
{
	animations[(int)iCurentSeqence].Update(dt);
}



