#include "Zombie.h"

#include "Player.h"

void Zombie::ChangeHealth(float changeHP)
{
}

bool Zombie::isDead()
{
	return false;
}

void Zombie::Movement(bool aim_R, bool aim_L, bool aim_U, bool aim_D, float dt)
{
	
}

void Zombie::CheckCollisions(std::vector<Object> obstacles)
{
	for (auto obs : obstacles) {
		this->object.IsOverLapping(obs, aimsRight, aimsLeft, aimsDown, aimsUp);
	}
}

void Zombie::DrawEnemy(Graphics& gtx)
{
}

void Zombie::Shoot()
{
}



Zombie::Zombie(Object object, float health, float probability, bool isAlive, int points) :Enemy(object, health, probability, isAlive, points) {
	for (int i = 0; i < (int)Sequences::StandDown; i++) {
		animations.emplace_back(Animation(32, 48 * i, 32, 48, 4, surface, 0.001f));
	}
	for (int i = (int)Sequences::StandDown; i < (int)Sequences::Count; i++) {
		animations.emplace_back(Animation(0, 48 * (i - (int)Sequences::StandDown), 32, 48, 1, surface, 0.001f));
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

Object Zombie::Getobject()const 
{
	return this->object;
}

void Zombie::CalculateDistance(const Vec2D& pos)
{
	distance = sqrt(pow(object.pos.x - pos.x, 2) + pow(object.pos.y - pos.y, 2));
}



