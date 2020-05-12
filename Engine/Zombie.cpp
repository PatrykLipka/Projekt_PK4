#include "Zombie.h"





bool Zombie::IsAlive()
{
	if (this->isAlive == true) return true;
	else return false;
}

void Zombie::PreMovement(float dt, const Object& playerObject, std::vector<Obstacle> obstacles, std::vector<Enemy*> enemies)
{
	float playerX = playerObject.pos.x;
	float playerY = playerObject.pos.y;
	
	float dirX = playerX - object.pos.x;
	float dirY = playerY - object.pos.y;
	
	float distance = sqrt(dirX * dirX + dirY * dirY);
	float desiredX = playerObject.width / 2 + object.width / 2;
	float desiredY = playerObject.height / 2 + object.height / 2;
	float desiredDistance = sqrt(desiredX * desiredX/4 + desiredY * desiredY/4);
	if (dirY < 0 && desiredDistance < distance) {
		Movement(false, false, true, false, dt, playerObject, obstacles, enemies, dirX, dirY);
		aimsRight = false;
		aimsLeft = false;
		aimsDown = false;
		aimsUp = true;
	}
	if (dirY > 0 && desiredDistance < distance) {
		Movement(false, false, false, true, dt, playerObject, obstacles, enemies, dirX, dirY);
		aimsRight = false;
		aimsLeft = false;
		aimsDown = true;
		aimsUp = false;
	}
	if (dirX > 0 && desiredDistance < distance) {
		Movement(true, false, false, false, dt, playerObject, obstacles, enemies, dirX, dirY);
		aimsRight = true;
		aimsLeft = false;
		aimsDown = false;
		aimsUp = false;
	}
	if (dirX < 0 && desiredDistance < distance) {
		Movement(false, true, false, false, dt, playerObject, obstacles, enemies, dirX, dirY);
		aimsRight = false;
		aimsLeft = true;
		aimsDown = false;
		aimsUp = false;
	}
	if (desiredDistance >= distance) {
		Movement(false, false, false, false, dt, playerObject, obstacles, enemies, dirX, dirY);
	}
}

void Zombie::Movement(bool aim_R, bool aim_L, bool aim_U, bool aim_D, float dt, const Object& playerObject, std::vector<Obstacle> obstacles, std::vector<Enemy*> enemies, float dirX, float dirY)
{
	if (aim_R) {
		aimsRight = true;
		aimsLeft = false;
		aimsDown = false;
		aimsUp = false;
		if (dirX > 36) iCurrentSeqence = Sequences::WalkingRight;
		else if (dirX < -36) iCurrentSeqence = Sequences::WalkingLeft;
		else if (dirX >= -36 && dirX <= 36 && dirY > 0) iCurrentSeqence = Sequences::WalkingDown;
		else if (dirX >= -36 && dirX <= 36 && dirY < 0) iCurrentSeqence = Sequences::WalkingUp;
		
		
		if ((object.hitbox.right += object.movement.x) < Graphics::ScreenWidth - 1)
			object.pos.x += object.movement.x;
		else {
			float dx = Graphics::ScreenWidth - object.hitbox.right + object.movement.x;
			object.pos.x += dx;
		}
	}
	else if (aim_L) {

		aimsRight = false;
		aimsLeft = true;
		aimsDown = false;
		aimsUp = false;
		if (dirX > 36) iCurrentSeqence = Sequences::WalkingRight;
		else if (dirX < -36) iCurrentSeqence = Sequences::WalkingLeft;
		else if (dirX >= -36 && dirX <= 36 && dirY > 0) iCurrentSeqence = Sequences::WalkingDown;
		else if (dirX >= -36 && dirX <= 36 && dirY < 0) iCurrentSeqence = Sequences::WalkingUp;
		
		if ((object.hitbox.left -= object.movement.x) > 0)
			object.pos.x -= object.movement.x;
		else {
			object.pos.x = object.width / 2;
		}
	}
	else if (aim_U) {
		aimsRight = false;
		aimsLeft = false;
		aimsDown = false;
		aimsUp = true;
		if (dirX > 36) iCurrentSeqence = Sequences::WalkingRight;
		else if (dirX < -36) iCurrentSeqence = Sequences::WalkingLeft;
		else if (dirX >= -36 && dirX <= 36 && dirY > 0) iCurrentSeqence = Sequences::WalkingDown;
		else if (dirX >= -36 && dirX <= 36 && dirY < 0) iCurrentSeqence = Sequences::WalkingUp;
		
		if ((object.hitbox.top -= object.movement.y) > 0)
			object.pos.y -= object.movement.y;
		else {

			object.pos.y = object.height / 2;
		}
	}
	else if (aim_D) {
		aimsRight = false;
		aimsLeft = false;
		aimsDown = true;
		aimsUp = false;
		if (dirX > 36) iCurrentSeqence = Sequences::WalkingRight;
		else if (dirX < -36) iCurrentSeqence = Sequences::WalkingLeft;
		else if (dirX >= -36 && dirX <= 36 && dirY > 0) iCurrentSeqence = Sequences::WalkingDown;
		else if (dirX >= -36 && dirX <= 36 && dirY < 0) iCurrentSeqence = Sequences::WalkingUp;
		
		if ((object.hitbox.bottom += object.movement.y) < Graphics::ScreenHeight - 1)
			object.pos.y += object.movement.y;
		else {
			float dy = Graphics::ScreenHeight - object.hitbox.bottom + object.movement.y;
			object.pos.y += dy;
		}

	}
	else {
		if (dirX >= 12) iCurrentSeqence = Sequences::StandRight;
		else if (dirX <= -12) iCurrentSeqence = Sequences::StandLeft;
		else if (dirX >= -12 && dirX <= 12 && dirY > 0) iCurrentSeqence = Sequences::StandDown;
		else if (dirX >= -12 && dirX <= 12 && dirY < 0) iCurrentSeqence = Sequences::StandUp;
		else {
			iCurrentSeqence = Sequences::StandDown;
		}
	}
	CheckCollisions(obstacles, enemies);
	object.hitbox.DoActualization(object.pos, object.width, object.height);
	Update(dt);

}



void Zombie::CheckCollisions(std::vector<Obstacle> obstacles, std::vector<Enemy*> enemies)
{
	for (auto obs : obstacles) {
		this->object.IsOverLapping(obs.getObject(), aimsRight, aimsLeft, aimsDown, aimsUp);
	}

	for (auto enem : enemies) {
		if (this != enem)
		{
			this->object.IsOverLapping(enem->GetObject(), aimsRight, aimsLeft, aimsDown, aimsUp);
		}
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
		animations.emplace_back(Animation(22, 40 * i, 22, 40, 4, surface, 0.15f));
	}
	for (int i = (int)Sequences::StandDown; i < (int)Sequences::Count; i++) {
		animations.emplace_back(Animation(0, 40 * (i - (int)Sequences::StandDown), 22, 40, 1, surface, 0.15f));
	}
}



void Zombie::Draw(Graphics& gfx)
{
	Vec2D pos{ object.hitbox.left,object.hitbox.top };
	animations[(int)iCurrentSeqence].Draw(pos, gfx);
}

void Zombie::Update(float dt)
{
	animations[(int)iCurrentSeqence].Update(dt);
}

Object Zombie::GetObject() 
{
	return this->object;
}

void Zombie::CalculateDistance(const Vec2D& pos)
{
	distance = sqrt(pow(object.pos.x - pos.x, 2) + pow(object.pos.y - pos.y, 2));
}

void Zombie::Hitted(const float & dmg)
{
	ChangeHealth(dmg);
}


void Zombie::ChangeHealth(float changeHP)
{
	
	if ((this->health -= changeHP) > 0) { isAlive = true; }
	else { isAlive = false; }
}
