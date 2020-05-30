#include "Player.h"

void Player::Movement(bool aim_R, bool aim_L, bool aim_U, bool aim_D, float dt, std::vector<Obstacle> obstacles, std::vector<std::unique_ptr<Enemy>>& enemies)
{ 
	if (aim_R) {
		isMoving = true;
		aimsRight = true;
		aimsLeft = false;
		aimsDown = false;
		aimsUp = false;
		iCurrentSeqence = Sequences::WalkingRight;
		Object obj = object;
		obj.pos.x += obj.movement.x;
		obj.hitbox.DoActualization(obj.pos, obj.width, obj.height);
		if ((object.hitbox.right += object.movement.x) < Graphics::ScreenWidth - 1) {
			if (CheckIfMovementPossible(enemies, obj))
				object.pos.x += object.movement.x;
		}
		else {
			float dx = Graphics::ScreenWidth - object.hitbox.right + object.movement.x;
			object.pos.x += dx;
		}
	}
	else if (aim_L) {
		isMoving = true;
		aimsRight = false;
		aimsLeft = true;
		aimsDown = false;
		aimsUp = false;
		iCurrentSeqence = Sequences::WalkingLeft;
		Object obj = object;
		obj.pos.x -= obj.movement.x;
		obj.hitbox.DoActualization(obj.pos, obj.width, obj.height);
		if ((object.hitbox.left -= object.movement.x) > 0) {
			if (CheckIfMovementPossible(enemies, obj))
				object.pos.x -= object.movement.x;
		}
		else {
			object.pos.x = object.width / 2;
		}
	}
	else if (aim_U) {
		isMoving = true;
		aimsRight = false;
		aimsLeft = false;
		aimsDown = false;
		aimsUp = true;
		iCurrentSeqence = Sequences::WalkingUp;
		Object obj = object;
		obj.pos.y -= obj.movement.y;
		obj.hitbox.DoActualization(obj.pos, obj.width, obj.height);
		if ((object.hitbox.top -= object.movement.y) > 0) {
			if (CheckIfMovementPossible(enemies, obj))
				object.pos.y -= object.movement.y;
		}
		else {

			object.pos.y = object.height / 2;
		}
	}
	else if (aim_D) {
		isMoving = true;
		aimsRight = false;
		aimsLeft = false;
		aimsDown = true;
		aimsUp = false;
		iCurrentSeqence = Sequences::WalkingDown;
		Object obj = object;
		obj.pos.y += obj.movement.y;
		obj.hitbox.DoActualization(obj.pos, obj.width, obj.height);
		if ((object.hitbox.bottom += object.movement.y) < Graphics::ScreenHeight - 1) {
			if (CheckIfMovementPossible(enemies, obj))
				object.pos.y += object.movement.y;
		}
		else {
			float dy = Graphics::ScreenHeight - object.hitbox.bottom + object.movement.y;
			object.pos.y += dy;
		}

	}
	else {
		isMoving = false;
		if (aim_D) iCurrentSeqence = Sequences::StandDown;
		else if (aim_R)iCurrentSeqence = Sequences::StandRight;
		else if (aim_L)iCurrentSeqence = Sequences::StandLeft;
		else if (aim_U)iCurrentSeqence = Sequences::StandUp;
	}
	CheckCollisions(obstacles);
	object.hitbox.DoActualization(object.pos, object.width, object.height);
	Update(dt);
}

void Player::CheckCollisions(std::vector<Obstacle> obstacles)
{
	for (auto obs : obstacles) {
		this->object.IsOverLapping(obs.getObject(), aimsRight, aimsLeft, aimsDown, aimsUp);
	}

	/*for (auto enem : enemies) {
			this->object.IsOverLapping(enem->GetObjectW(), aimsRight, aimsLeft, aimsDown, aimsUp);
	}*/ //powoduje dziwne zachowanie
}

bool Player::CheckIfMovementPossible(std::vector<std::unique_ptr<Enemy>>& enemies, const Object& nextPosition)
{
	for (auto& enemy : enemies) {
		if (!enemy->GetObjectW().hitbox.IsOverLappingForEnemies(nextPosition.pos)) {}
		else { return false; }
	}
	return true;
}

void Player::Draw(Graphics& gfx)
{
	Vec2D pos{ object.hitbox.left,object.hitbox.top };
	if (!isHitted)
		animations[(int)iCurrentSeqence].Draw(pos, gfx);
	else {
		animations[(int)iCurrentSeqence].DrawH(pos, gfx);
		isHitted = false;
	}
}

void Player::Update(float dt)
{
	animations[(int)iCurrentSeqence].Update(dt);
}

void Player::Shot(std::vector<std::unique_ptr<Enemy>>& enemies, float dt, std::vector<Obstacle>obstacles, Graphics& gfx)
{
	isShooting = weapon->Shoot(aimsRight, aimsLeft, aimsDown, aimsUp, enemies, obstacles, object.pos, dt,isMoving);
}

void Player::DrawShot(Graphics& gfx, float dt)
{
	if (isShooting)
		isShooting = weapon->DrawShot(gfx, dt);

}


void Player::LoadSurface()
{
	animations.clear();
	for (int i = 0; i < (int)Sequences::StandDown; i++) {
		animations.emplace_back(Animation(0, (int)object.height * i, (int)object.width, (int)object.height, 4, surface, 0.1f));
	}
	for (int i = (int)Sequences::StandDown; i < (int)Sequences::Count; i++) {
		animations.emplace_back(Animation(0, (int)object.height * (i - (int)Sequences::StandDown), (int)object.width, (int)object.height, 1, surface, 0.1f));
	}
	/*for (int i = 0; i < (int)Sequences::StandDown; i++) {
		animations.emplace_back(Animation(5 * (int)object.width, (int)object.height * i, (int)object.width, (int)object.height, 4, surface, 0.1f));
	}*/
	
}

void Player::ChangeSurface()
{
	if (typeid(*weapon) == typeid(Glock)) {
		surface = surfaceGlock;
		LoadSurface();
	}
	else if (typeid(*weapon) == typeid(Uzi)) {
		surface = surfaceUzi;
		LoadSurface();
	}
	else if (typeid(*weapon) == typeid(Shotgun)) {
		surface = surfaceShotgun;
		LoadSurface();
	}
	else if (typeid(*weapon) == typeid(Sharpshooter)) {
		surface = surfaceSniper;
		LoadSurface();
	}
}

void Player::Upgrade(size_t hash_code, int number)
{
	for (auto gun : ownedGuns) {
		if (typeid(*gun).hash_code() == hash_code)
		{
			gun->Upgrade(number);
		}
	}
}



Player::Player(Object obj, float hel, bool isAlive, std::shared_ptr<Weapon> gun) :object(obj), health(hel), isAlive(isAlive), weapon(gun)
{
	ownedGuns.push_back(weapon);
	aimsRight = false;
	aimsLeft = false;
	aimsDown = true;
	aimsUp = false;
	LoadSurface();
}

Object Player::getObject()
{
	return object;
}

void Player::ChangeHealth(float changeHP)
{
	if ((this->health -= changeHP) > 0) {
		isAlive = true;
		isHitted = true;
	}
	else {
		isAlive = false;
	}
}

bool Player::IsAlive()
{
	if (this->isAlive == true) return true;
	else return false;
}

void Player::SetNewOwnedGun(std::shared_ptr<Weapon> gun)
{
	ownedGuns.push_back(gun);
}

int Player::GetSizeOfOwnedGuns()
{
	return ownedGuns.size();
}

void Player::AddAmoTuGun(std::size_t hash_code, int amo)
{
	for (auto gun : ownedGuns) {
		if (typeid(*gun).hash_code() == hash_code)
		{
			gun->AddAmo(amo); break;
		}
	}
}

void Player::Recover(float hp)
{
	health += hp;
	if (health > 0) isAlive = true;
}

bool Player::ChangeGunForNextGun()
{
	for (std::vector<std::shared_ptr<Weapon>>::iterator it = ownedGuns.begin(); it < ownedGuns.end(); it++) {
		if (*it == weapon) {
			if (it == (--ownedGuns.end())) {
				weapon = ownedGuns[0];
				ChangeSurface();
			}
			else {
				weapon = *(++it);
				ChangeSurface();
				break;
			}
		}
	}
	return true;
}

bool Player::ChangeGunForPreviousGun()
{
	for (std::vector<std::shared_ptr<Weapon>>::iterator it = ownedGuns.begin(); it < ownedGuns.end(); it++) {
		if (*it == weapon) {
			if (it == ownedGuns.begin()) {
				weapon = *(--ownedGuns.end());
				ChangeSurface();
				break;
			}
			else {
				weapon = *(--it);
				ChangeSurface();
				break;
			}
		}
	}
	return true;
}

std::string Player::GetInformationAboutCurrentGun()
{
	return "Hp:" + std::to_string(int(health)) + weapon->GetInformationAboutCurrentGun();
}

std::string Player::GetCurrentWeaponName()
{
	return weapon->GetName();
}


