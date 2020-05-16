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

	if (blockedRight || blockedLeft || blockedUp || blockedDown) {
		if (blockedRight) {
			aimsRight = false;
			aimsLeft = false;
			aimsUp = false;
			aimsDown = true;
			
			Movement(false, false, false, true, dt, playerObject, obstacles, enemies, dirX, dirY, distance);
			
		}
		if (blockedLeft) {
			aimsRight = false;
			aimsLeft = false;
			aimsUp = true;
			aimsDown = false;
			
			Movement(false, false, true, false, dt, playerObject, obstacles, enemies, dirX, dirY, distance);
			
		}
		if (blockedUp) {
			aimsRight = true;
			aimsLeft = false;
			aimsUp = false;
			aimsDown = false;
			
			Movement(true, false, false, false, dt, playerObject, obstacles, enemies, dirX, dirY, distance);
			
		}
		if (blockedDown) {
			aimsRight = false;
			aimsLeft = true;
			aimsUp = false;
			aimsDown = false;
			
			Movement(false, true, false, false, dt, playerObject, obstacles, enemies, dirX, dirY, distance);
			
		}
	}
	else{
		if (dirY < 0 && desiredDistance < distance) {
			aimsRight = false;
			aimsLeft = false;
			aimsDown = false;
			aimsUp = true;
			Movement(false, false, true, false, dt, playerObject, obstacles, enemies, dirX, dirY, distance);
			
		}
		if (dirY > 0 && desiredDistance < distance) {
			aimsRight = false;
			aimsLeft = false;
			aimsDown = true;
			aimsUp = false;
			Movement(false, false, false, true, dt, playerObject, obstacles, enemies, dirX, dirY, distance);
			
		}
		if (dirX > 0 && desiredDistance < distance) {
			aimsRight = true;
			aimsLeft = false;
			aimsDown = false;
			aimsUp = false;
			Movement(true, false, false, false, dt, playerObject, obstacles, enemies, dirX, dirY, distance);
			
		}
		if (dirX < 0 && desiredDistance < distance) {
			aimsRight = false;
			aimsLeft = true;
			aimsDown = false;
			aimsUp = false;
			Movement(false, true, false, false, dt, playerObject, obstacles, enemies, dirX, dirY, distance);
			
		}
		if (desiredDistance >= distance) {
			Movement(false, false, false, false, dt, playerObject, obstacles, enemies, dirX, dirY, distance);
		}
	}
}

void Zombie::Movement(bool aim_R, bool aim_L, bool aim_U, bool aim_D, float dt, const Object& playerObject, std::vector<Obstacle> obstacles, std::vector<Enemy*> enemies, float dirX, float dirY, float distance)
{
	float previousX = object.pos.x;
	float previousY = object.pos.y;

	float playerX = playerObject.pos.x;
	float playerY = playerObject.pos.y;

	float distanceX = sqrt(dirX * dirX);
	float distanceY = sqrt(dirY * dirY);

	float distanceToBlock = 100;

	bool blockedByWall= false;

	if (aim_R) {
		aimsRight = true;
		aimsLeft = false;
		aimsDown = false;
		aimsUp = false;
		if (blockedUp) {
			blockedUp = false;
			if (dirX <= 5) {
				/*if ((object.hitbox.top -= object.movement.y) <= 0) {
					object.pos.x -= 2 * object.movement.x;
				}
				else */if ((object.hitbox.right += object.movement.x) < Graphics::ScreenWidth - 1) {
					object.pos.x += object.movement.x;
				}					
				else {
					float dx = Graphics::ScreenWidth - object.hitbox.right + object.movement.x;
					object.pos.x += dx;
				}
				//CheckCollisions(obstacles, enemies);
			}
		}
		
		
		if (dirX > 36) iCurrentSeqence = Sequences::WalkingRight;
		else if (dirX < -36) iCurrentSeqence = Sequences::WalkingLeft;
		else if (dirX >= -36 && dirX <= 36 && dirY > 0) iCurrentSeqence = Sequences::WalkingDown;
		else if (dirX >= -36 && dirX <= 36 && dirY < 0) iCurrentSeqence = Sequences::WalkingUp;
		
		if ((object.hitbox.right += object.movement.x) < Graphics::ScreenWidth - 1)
			object.pos.x += object.movement.x;
		else {
			float dx = Graphics::ScreenWidth - object.hitbox.right + object.movement.x;
			object.pos.x += dx;
			blockedByWall = true;
		}
		CheckCollisions(obstacles, enemies);
		if (previousX + object.movement.x > object.pos.x && (distanceX >= distanceY || distance >= distanceToBlock) && !blockedByWall){
			blockedRight = true;
		}
		else {
			blockedRight = false;
		}
			
	}
	
	
	else if (aim_L) {

		aimsRight = false;
		aimsLeft = true;
		aimsDown = false;
		aimsUp = false;
		if (blockedDown) {
			blockedDown = false;
			if (dirX >= -5) {
				/*if ((object.hitbox.bottom += object.movement.y) >= Graphics::ScreenHeight - 1) {
					object.pos.x += 2 * object.movement.x;
				}		
				else */if ((object.hitbox.left -= object.movement.x) > 0) {
					object.pos.x -= object.movement.x;
				}
				else {

					object.pos.x = object.height / 2;
				}
				//CheckCollisions(obstacles, enemies);
			}
		}

		if (dirX > 36) iCurrentSeqence = Sequences::WalkingRight;
		else if (dirX < -36) iCurrentSeqence = Sequences::WalkingLeft;
		else if (dirX >= -36 && dirX <= 36 && dirY > 0) iCurrentSeqence = Sequences::WalkingDown;
		else if (dirX >= -36 && dirX <= 36 && dirY < 0) iCurrentSeqence = Sequences::WalkingUp;

		if ((object.hitbox.left -= object.movement.x) > 0)
			object.pos.x -= object.movement.x;
		else {
			object.pos.x = object.width / 2;
			blockedByWall = true;
		}
		CheckCollisions(obstacles, enemies);

		if (previousX - object.movement.x < object.pos.x &&  (distanceX >= distanceY || distance >= distanceToBlock) && !blockedByWall){
			blockedLeft = true;
		}
		else {
			blockedLeft = false;
		}
	}
	
	else if (aim_U) {
		aimsRight = false;
		aimsLeft = false;
		aimsDown = false;
		aimsUp = true;
		if (blockedLeft) {
			blockedLeft = false;
			if (dirY >= -5) {
				/*if ((object.hitbox.left -= object.movement.x) <= 0) {
					object.pos.y += 2 * object.movement.y;
				}				
				else */if ((object.hitbox.top -= object.movement.y) > 0) {
					object.pos.y -= object.movement.y;
				}
				else {

					object.pos.y = object.height / 2;
				}
				//CheckCollisions(obstacles, enemies);
			}
		}
		
		if (dirX > 36) iCurrentSeqence = Sequences::WalkingRight;
		else if (dirX < -36) iCurrentSeqence = Sequences::WalkingLeft;
		else if (dirX >= -36 && dirX <= 36 && dirY > 0) iCurrentSeqence = Sequences::WalkingDown;
		else if (dirX >= -36 && dirX <= 36 && dirY < 0) iCurrentSeqence = Sequences::WalkingUp;
		
		if ((object.hitbox.top -= object.movement.y) > 0)
			object.pos.y -= object.movement.y;
		else {
			object.pos.y = object.height / 2;
			blockedByWall = true;
		}
		CheckCollisions(obstacles, enemies);

		if (previousY - object.movement.y < object.pos.y && ( distanceX <=  distanceY || distance >= distanceToBlock) && !blockedByWall)
		{
			blockedUp = true;
		}
		else {
			blockedUp= false;
		}
	}
	
	
	else if (aim_D) {
		aimsRight = false;
		aimsLeft = false;
		aimsDown = true;
		aimsUp = false;
		if (blockedRight) {
			blockedRight = false;
			if (dirY <= 5) {
				/*if ((object.hitbox.right += object.movement.x) >= Graphics::ScreenWidth - 1) {
					object.pos.y -= 2 * object.movement.y;
				}
				else */if ((object.hitbox.bottom += object.movement.y) < Graphics::ScreenHeight - 1) {
					object.pos.y += object.movement.y;
				}
				else {
					float dy = Graphics::ScreenHeight - object.hitbox.bottom + object.movement.y;
					object.pos.y += dy;
				}
				//CheckCollisions(obstacles, enemies);
			}
		}
		
		if (dirX > 36) iCurrentSeqence = Sequences::WalkingRight;
		else if (dirX < -36) iCurrentSeqence = Sequences::WalkingLeft;
		else if (dirX >= -36 && dirX <= 36 && dirY > 0) iCurrentSeqence = Sequences::WalkingDown;
		else if (dirX >= -36 && dirX <= 36 && dirY < 0) iCurrentSeqence = Sequences::WalkingUp;
		
		if ((object.hitbox.bottom += object.movement.y) < Graphics::ScreenHeight - 1)
			object.pos.y += object.movement.y;
		else {
			float dy = Graphics::ScreenHeight - object.hitbox.bottom + object.movement.y;
			object.pos.y += dy;
			blockedByWall = true;
		}
		CheckCollisions(obstacles, enemies);
		if (previousY + object.movement.y > object.pos.y && (distanceX <= distanceY || distance>= distanceToBlock) && !blockedByWall)
		{
			blockedDown = true;
		}
		else {
			blockedDown = false;
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
			this->object.IsOverLapping(enem->GetObjectW(), aimsRight, aimsLeft, aimsDown, aimsUp);
		}
	}

}


bool Zombie::IsOverLappingObject(const Object other)
{
	if (this->object.hitbox.IsOverLapping(other.hitbox)) {
		return true;
	}
	else {
		return false;
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
	if(!isHitted)
	animations[(int)iCurrentSeqence].Draw(pos, gfx);
	else
	{
	animations[(int)iCurrentSeqence].DrawH(pos, gfx);
	isHitted = false; 
	}
}

void Zombie::Update(float dt)
{
	animations[(int)iCurrentSeqence].Update(dt);
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
