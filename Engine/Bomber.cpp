#include "Bomber.h"


bool compare_distanceBomber(std::unique_ptr<Enemy>& obj1, std::unique_ptr<Enemy>& obj2) {
	if (obj1 && obj2)
		return obj1->distance < obj2->distance;
	return true;
}

bool Bomber::IsAlive()
{
	if (this->isAlive == true) return true;
	else return false;
}

float Bomber::PreMovement(float dt, const Object& playerObject, std::vector<Obstacle> obstacles, std::vector<std::unique_ptr<Enemy>>& enemies, int& delay)
{
	float playerX = playerObject.pos.x;
	float playerY = playerObject.pos.y;

	float dirX = playerX - object.pos.x;
	float dirY = playerY - object.pos.y;

	float distance = sqrt(dirX * dirX + dirY * dirY);
	float desiredX = playerObject.width / 2 + object.width / 2;
	float desiredY = playerObject.height / 2 + object.height / 2;
	float desiredDistance = sqrt(desiredX * desiredX / 4 + desiredY * desiredY / 4);

	float damageToPlayer = 0;

	if (health >0 && (3*attackRange/5 >= distance || attackIterator > 0)) {
		dirX = playerX - object.pos.x;
		dirY = playerY - object.pos.y;
		attackIterator++;
		if (attackIterator == 1)
		{
			attackX = dirX; 
			attackY = dirY;
		}
		if (attackX > 16) iCurrentSeqence = Sequences::AttackRight;
		else if (attackX < -16) iCurrentSeqence = Sequences::AttackLeft;
		else if (attackX >= -16 && attackX <= 16 && attackY > 0) iCurrentSeqence = Sequences::AttackDown;
		else if (attackX >= -16 && attackX <= 16 && attackY < 0) iCurrentSeqence = Sequences::AttackUp;
		Update(dt);
		
	}
	else {
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
		else {
			if (dirY < 0 && desiredDistance < distance && attackIterator == 0) {
				aimsRight = false;
				aimsLeft = false;
				aimsDown = false;
				aimsUp = true;
				Movement(false, false, true, false, dt, playerObject, obstacles, enemies, dirX, dirY, distance);

			}
			if (dirY > 0 && desiredDistance < distance && attackIterator == 0) {
				aimsRight = false;
				aimsLeft = false;
				aimsDown = true;
				aimsUp = false;
				Movement(false, false, false, true, dt, playerObject, obstacles, enemies, dirX, dirY, distance);

			}
			if (dirX > 0 && desiredDistance < distance && attackIterator == 0) {
				aimsRight = true;
				aimsLeft = false;
				aimsDown = false;
				aimsUp = false;
				Movement(true, false, false, false, dt, playerObject, obstacles, enemies, dirX, dirY, distance);

			}
			if (dirX < 0 && desiredDistance < distance && attackIterator == 0) {
				aimsRight = false;
				aimsLeft = true;
				aimsDown = false;
				aimsUp = false;
				Movement(false, true, false, false, dt, playerObject, obstacles, enemies, dirX, dirY, distance);

			}
			if (desiredDistance >= distance && attackIterator == 0) {
				Movement(false, false, false, false, dt, playerObject, obstacles, enemies, dirX, dirY, distance);
			}
		}
	}
	if (health <= 0)
	{
		attackIterator++;
		if (attackIterator == 1)
		{
			attackX = dirX;
			attackY = dirY;
		}
		if (attackX > 16) iCurrentSeqence = Sequences::AttackRight;
		else if (attackX < -16) iCurrentSeqence = Sequences::AttackLeft;
		else if (attackX >= -16 && attackX <= 16 && attackY > 0) iCurrentSeqence = Sequences::AttackDown;
		else if (attackX >= -16 && attackX <= 16 && attackY < 0) iCurrentSeqence = Sequences::AttackUp;
		Update(dt);
	}
	damageToPlayer = Attack(distance, dt, enemies, delay);
	return damageToPlayer;
}

void Bomber::Movement(bool aim_R, bool aim_L, bool aim_U, bool aim_D, float dt, const Object& playerObject, std::vector<Obstacle> obstacles, std::vector<std::unique_ptr<Enemy>>& enemies, float dirX, float dirY, float distance)
{
	float previousX = object.pos.x;
	float previousY = object.pos.y;

	float playerX = playerObject.pos.x;
	float playerY = playerObject.pos.y;

	float distanceX = sqrt(dirX * dirX);
	float distanceY = sqrt(dirY * dirY);

	float distanceToBlock = 15;


	bool blockedByWall = false;

	if (aim_R) {
		aimsRight = true;
		aimsLeft = false;
		aimsDown = false;
		aimsUp = false;
		if (blockedUp) {
			blockedUp = false;
			if (dirX <= 5) {
				if ((object.hitbox.right += object.movement.x) < Graphics::ScreenWidth - 1) {
					object.pos.x += object.movement.x;
				}
				else {
					float dx = Graphics::ScreenWidth - object.hitbox.right + object.movement.x;
					object.pos.x += dx;
				}
				CheckCollisions(obstacles, enemies);
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
		if (previousX + object.movement.x > object.pos.x && (distanceX >= distanceY || distance >= distanceToBlock) && !blockedByWall) {
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
				if ((object.hitbox.left -= object.movement.x) > 0) {
					object.pos.x -= object.movement.x;
				}
				else {

					object.pos.x = object.height / 2;
				}
				CheckCollisions(obstacles, enemies);
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

		if (previousX - object.movement.x < object.pos.x && (distanceX >= distanceY || distance >= distanceToBlock) && !blockedByWall) {
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
				if ((object.hitbox.top -= object.movement.y) > 0) {
					object.pos.y -= object.movement.y;
				}
				else {

					object.pos.y = object.height / 2;
				}
				CheckCollisions(obstacles, enemies);
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

		if (previousY - object.movement.y < object.pos.y && (distanceX <= distanceY || distance >= distanceToBlock) && !blockedByWall)
		{
			blockedUp = true;
		}
		else {
			blockedUp = false;
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
				if ((object.hitbox.bottom += object.movement.y) < Graphics::ScreenHeight - 1) {
					object.pos.y += object.movement.y;
				}
				else {
					float dy = Graphics::ScreenHeight - object.hitbox.bottom + object.movement.y;
					object.pos.y += dy;
				}
				CheckCollisions(obstacles, enemies);
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
		if (previousY + object.movement.y > object.pos.y && (distanceX <= distanceY || distance >= distanceToBlock) && !blockedByWall)
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





void Bomber::CheckCollisions(std::vector<Obstacle> obstacles, std::vector<std::unique_ptr<Enemy>>& enemies)
{
	for (auto obs : obstacles) {
		this->object.IsOverLapping(obs.getObject(), aimsRight, aimsLeft, aimsDown, aimsUp);
	}

	for (auto& enem : enemies) {
		if (this != enem.get())//potencjalnie mo¿e byæ problem
		{
			this->object.IsOverLapping(enem->GetObjectW(), aimsRight, aimsLeft, aimsDown, aimsUp);
		}
	}

}


bool Bomber::IsOverLappingObject(const Object other)
{
	if (this->object.hitbox.IsOverLapping(other.hitbox)) {
		return true;
	}
	else {
		return false;
	}
}


void Bomber::DrawEnemy(Graphics& gtx)
{
}

float Bomber::Attack(float distanceToPlayer, float dt)
{
	return 0;
}

bool Bomber::SortByDistance(std::unique_ptr<Enemy>& obj1, std::unique_ptr<Enemy>& obj2) {
	if (obj1 && obj2)
		return CalculateDistanceToEnemy(obj1.get()->GetObjectW().pos) < CalculateDistanceToEnemy(obj2.get()->GetObjectW().pos);

	return true;
}

float Bomber::Attack(float distanceToPlayer, float dt, std::vector<std::unique_ptr<Enemy>>& enemies, int& delay)
{
	
	if (attackIterator > 55+delay)
	{
		attackIterator = 0;
		delay+=20;
		std::vector<std::unique_ptr<Enemy>> enemiesHit;
		CalculateExplosion(enemies, enemiesHit);	
		std::sort(enemiesHit.begin(), enemiesHit.end(), compare_distanceBomber);
		enemies.erase(std::remove_if(enemies.begin(), enemies.end(), [](std::unique_ptr<Enemy>& e) {if (e)return !e->IsAlive(); else return true; }), enemies.end());
		HitEnemies(enemies, enemiesHit);
		this->ChangeHealth(health);
		this->isAlive = false;
		if (distanceToPlayer <= attackRange) {
			Update(dt);
			return damage;
		}
		else {
			Update(dt);
			return 0;
		}
	}
	else {
		Update(dt);
		return 0;
	}
}

void Bomber::HitEnemies(std::vector<std::unique_ptr<Enemy>>& enemies, std::vector<std::unique_ptr<Enemy>>& enemiesHit)
{
	for (auto& enem : enemiesHit) {
		if (this != enem.get())
		{
			enem->ChangeHealth(damage);
			enem->isHitted = true;
		}
	}
	MergeVector(enemies, enemiesHit);
}



void Bomber::MergeVector(std::vector<std::unique_ptr<Enemy>>& enemies, std::vector<std::unique_ptr<Enemy>>& enemiesHit)
{	
	std::sort(enemies.begin(), enemies.end(), compare_distanceBomber);
	for (auto& e : enemiesHit) {
		enemies.push_back(std::move(e));
		std::sort(enemies.begin(), enemies.end(), compare_distanceBomber);
	}
}

Bomber::Bomber(Object object, float health, float damage, float probability, bool isAlive, int points) :Enemy(object, health, damage, probability, isAlive, points) {
	aimsRight = false;
	aimsLeft = false;
	aimsDown = true;
	aimsUp = false;
	attackRange = 80;
	value = 1;
	for (int i = 0; i < (int)Sequences::StandDown; i++) {
		animations.emplace_back(Animation(22, 46 * i, 22, 46, 4, surface, 0.15f));
	}
	for (int i = (int)Sequences::StandDown; i < (int)Sequences::AttackDown; i++) {
		animations.emplace_back(Animation(0, 46 * (i - (int)Sequences::StandDown), 22, 46, 1, surface, 0.15f));
	}
	for (int i = (int)Sequences::AttackDown; i < (int)Sequences::Count; i++) {
		animations.emplace_back(Animation(110, 46 * (i - (int)Sequences::AttackDown), 22, 46, 5, surface, 0.4f));
	}

}



void Bomber::Draw(Graphics& gfx)
{
	Vec2D pos{ object.hitbox.left,object.hitbox.top };
	if (!isHitted)
		animations[(int)iCurrentSeqence].Draw(pos, gfx);
	else
	{
		animations[(int)iCurrentSeqence].DrawH(pos, gfx);
		isHitted = false;
	}
}

void Bomber::Update(float dt)
{
	animations[(int)iCurrentSeqence].Update(dt);
}

void Bomber::CalculateExplosion(std::vector<std::unique_ptr<Enemy>>& enemies, std::vector<std::unique_ptr<Enemy>>& enemiesHit)
{
	for (auto& enem : enemies) {
		if (this != enem.get())
		{
			if ((enem->distance=CalculateDistanceToEnemy(enem->GetObjectW().pos)) <= attackRange) {
				enemiesHit.push_back(std::move(enem));
			}
		}
	}
}

void Bomber::CalculateDistance(const Vec2D& pos)
{
	distance = sqrt(pow(object.pos.x - pos.x, 2) + pow(object.pos.y - pos.y, 2));
}

float Bomber::CalculateDistanceToEnemy(const Vec2D& pos)
{
	float distance = sqrt(pow(object.pos.x - pos.x, 2) + pow(object.pos.y - pos.y, 2));
	return distance;
}

void Bomber::Hitted(const float& dmg)
{
	ChangeHealth(dmg);
}

Rect Bomber::GetBoom()
{
	return Rect(object.pos.x-64,object.pos.x+ 64,object.pos.y- 64,object.pos.y+ 64);
}

bool Bomber::Boom(Graphics& gfx,float dt)
{
	currenttime += dt;
	if (currenttime <= holdTime) {
		gfx.DrawBoom(GetBoom().left,GetBoom().top,GetBoom().right,GetBoom().bottom, Surface("explosion.png", 128, 128), Colors::MakeRGB(255,0,128));
		return false;
	}
	else {
		animationOver = true; return true;
	}
}


void Bomber::ChangeHealth(float changeHP)
{
	/*if ((*/this->health -= changeHP;/*) > 0) { isAlive = true; }
	else { isAlive = false; Points::IncrementPoints(value); }*/
}
