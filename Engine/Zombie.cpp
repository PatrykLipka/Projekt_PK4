#include "Zombie.h"



void Zombie::ChangeHealth(float changeHP)
{
}

bool Zombie::isDead()
{
	return false;
}

void Zombie::Movement(float dt, const Object& playerObject)
{
	float playerX = playerObject.pos.x-32;
	float playerY = playerObject.pos.y;

	float dirX = playerX - object.pos.x;
	float dirY = playerY - object.pos.y;

	float distance = sqrt(dirX * dirX + dirY * dirY);
	float desiredX = playerObject.width / 2 + object.width / 2;
	float desiredY = playerObject.height / 2 + object.height / 2;
	float desiredDistance = sqrt(desiredX * desiredX/4 + desiredY * desiredY/4);

	

	
	if (dirX > 0 && dirY == 0 && desiredDistance < distance) {
		aimsRight = true;
		aimsLeft = false;
		aimsDown = false;
		aimsUp = false;
		iCurrentSeqence = Sequences::WalkingRight;

		object.pos.x += object.movement.x;
	}
	else if (dirX < 0 && dirY == 0 && desiredDistance < distance) {

		aimsRight = false;
		aimsLeft = true;
		aimsDown = false;
		aimsUp = false;
		iCurrentSeqence = Sequences::WalkingLeft;
		
		object.pos.x -= object.movement.x;
	}
	else if (dirY > 0 && dirX == 0 && desiredDistance < distance) {
		aimsRight = false;
		aimsLeft = false;
		aimsDown = false;
		aimsUp = true;
		iCurrentSeqence = Sequences::WalkingDown;

		object.pos.y += object.movement.y;
	}
	else if (dirY < 0 && dirX == 0 && desiredDistance < distance) {
		aimsRight = false;
		aimsLeft = false;
		aimsDown = true;
		aimsUp = false;
		iCurrentSeqence = Sequences::WalkingUp;
		
		object.pos.y -= object.movement.y;
	}
	else if (dirX > 0 && dirY > 0 && desiredDistance < distance) {
		aimsRight = true;
		aimsLeft = false;
		aimsDown = false;
		aimsUp = false;
		iCurrentSeqence = Sequences::WalkingRight;

		object.pos.x += object.movement.x;
		object.pos.y += object.movement.y;
	}
	else if (dirX > 0 && dirY < 0 && desiredDistance < distance) {
		aimsRight = true;
		aimsLeft = false;
		aimsDown = false;
		aimsUp = false;
		iCurrentSeqence = Sequences::WalkingRight;

		object.pos.x += object.movement.x;
		object.pos.y -= object.movement.y;
		
	}

	else if (dirX < 0 && dirY > 0 && desiredDistance < distance) {
		aimsRight = true;
		aimsLeft = false;
		aimsDown = false;
		aimsUp = false;
		iCurrentSeqence = Sequences::WalkingLeft;

		object.pos.x -= object.movement.x;
		object.pos.y += object.movement.y;
	}
	else if (dirX < 0 && dirY < 0 && desiredDistance < distance) {
		aimsRight = true;
		aimsLeft = false;
		aimsDown = false;
		aimsUp = false;
		iCurrentSeqence = Sequences::WalkingLeft;
		
		object.pos.x -= object.movement.x;
		object.pos.y -= object.movement.y;
	}

	else {
		if (dirX > 12) iCurrentSeqence = Sequences::StandRight;
		else if (dirX < -12) iCurrentSeqence = Sequences::StandLeft;
		else if (dirX >= -12 && dirX <= 12 && dirY > 0) iCurrentSeqence = Sequences::StandDown;
		else if (dirX >= -12 && dirX <= 12 && dirY < 0) iCurrentSeqence = Sequences::StandUp;
		else {
			iCurrentSeqence = Sequences::StandDown;
		}
	}
	object.hitbox.DoActualization(object.pos, object.width, object.height);
	Update(dt);

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

void Zombie::Attack()
{
}

Zombie::Zombie(Object object, float health, float probability, bool isAlive, int points) :Enemy(object, health, probability, isAlive, points) {
	aimsRight = false;
	aimsLeft = false;
	aimsDown = true;
	aimsUp = false;
	for (int i = 0; i < (int)Sequences::StandDown; i++) {
		animations.emplace_back(Animation(32, 48 * i, 32, 48, 4, surface, 0.15f));
	}
	for (int i = (int)Sequences::StandDown; i < (int)Sequences::Count; i++) {
		animations.emplace_back(Animation(0, 48 * (i - (int)Sequences::StandDown), 32, 48, 1, surface, 0.15f));
	}
}

void Zombie::Draw(Graphics& gfx)
{
	Vec2D pos{ object.hitbox.right,object.hitbox.top };
	animations[(int)iCurrentSeqence].Draw(pos, gfx);
}

void Zombie::Update(float dt)
{
	animations[(int)iCurrentSeqence].Update(dt);
}



