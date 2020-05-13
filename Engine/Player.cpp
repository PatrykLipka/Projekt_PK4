#include "Player.h"

void Player::Movement(bool aim_R, bool aim_L, bool aim_U, bool aim_D, float dt, std::vector<Obstacle> obstacles, std::vector<Enemy*> enemies)
{
	if (aim_R) {
		aimsRight = true;
		aimsLeft = false;
		aimsDown = false;
		aimsUp = false;
		iCurrentSeqence = Sequences::WalkingRight;
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
		iCurrentSeqence = Sequences::WalkingLeft;
		if ((object.hitbox.left -= object.movement.x) > 0)
		object.pos.x -= object.movement.x;
		else {
			object.pos.x =object.width/2;
		}
	}
	else if (aim_U) {
		aimsRight = false;
		aimsLeft = false;
		aimsDown = false;
		aimsUp = true;
		iCurrentSeqence = Sequences::WalkingUp;
		if ((object.hitbox.top -= object.movement.y )> 0)
		object.pos.y -= object.movement.y;
		else {
			
			object.pos.y = object.height/2;
		}
	}
	else if(aim_D){
		aimsRight = false;
		aimsLeft = false;
		aimsDown = true;
		aimsUp = false;
		iCurrentSeqence = Sequences::WalkingDown;
		if ((object.hitbox.bottom += object.movement.y) < Graphics::ScreenHeight - 1)
		object.pos.y += object.movement.y;
		else {
			float dy = Graphics::ScreenHeight - object.hitbox.bottom + object.movement.y;
			object.pos.y += dy;
		}
	
	}
	else {
		if (aim_D) iCurrentSeqence = Sequences::StandDown;
		else if (aim_R)iCurrentSeqence = Sequences::StandRight;
		else if (aim_L)iCurrentSeqence = Sequences::StandLeft; 
		else if (aim_U)iCurrentSeqence = Sequences::StandUp; 
	}
	CheckCollisions(obstacles, enemies);
	object.hitbox.DoActualization(object.pos,object.width,object.height);
	Update(dt);
}

void Player::CheckCollisions(std::vector<Obstacle> obstacles, std::vector<Enemy*> enemies)
{
	for (auto obs : obstacles) {
		this->object.IsOverLapping(obs.getObject(), aimsRight, aimsLeft, aimsDown, aimsUp);
	}

	/*for (auto enem : enemies) {
		this->object.IsOverLapping(enem->GetObject(), aimsRight, aimsLeft, aimsDown, aimsUp);
	}*/
	//to po odkomentowaniu powoduje dziwne zachowanie
}

void Player::Draw( Graphics & gfx)
{
	Vec2D pos{ object.hitbox.left,object.hitbox.top };
	animations[(int)iCurrentSeqence].Draw(pos, gfx);
}

void Player::Update(float dt)
{
	animations[(int)iCurrentSeqence].Update(dt);
}

void Player::Shot(std::vector<Enemy*> enemy,float dt, std::vector<Obstacle>obstacles, Graphics& gfx)
{	
	isShooting=weapon->Shoot(aimsRight, aimsLeft, aimsDown, aimsUp, enemy,obstacles, object.pos,dt);
}


//void Player::CheckCrate(std::vector<Crate>& crates)
//{
//	int iterator = 0;
//	for (auto crt : crates) {
//		if (crt.Collected(this->object)){
//			this->health = 100;
//			//odnawianie amunicji
//			crates.erase(crates.begin()+iterator);
//			break;
//		}
//		iterator++;
//	}
//}

Player::Player(Object obj, float hel,bool isAlive,Weapon * weapon):object(obj),health(hel),isAlive(isAlive),weapon(weapon)
{
	aimsRight = false;
	aimsLeft = false;
	aimsDown = true;
	aimsUp = false;
	for (int i = 0; i < (int)Sequences::StandDown; i++) {
		animations.emplace_back(Animation(0, obj.height * i, obj.width, obj.height, 4, surface, 0.1f));
	}
	for (int i = (int)Sequences::StandDown; i < (int)Sequences::StandDownWithShot; i++) {
		animations.emplace_back(Animation(0, obj.height * (i-(int)Sequences::StandDown), obj.width, obj.height ,1, surface, 0.1f));
	}
	for (int i = 0; i < (int)Sequences::StandDownWithShot; i++) {
		animations.emplace_back(Animation(5*obj.width, obj.height * i, obj.width, obj.height, 4, surface, 0.1f));
	}
	for (int i = (int)Sequences::StandDownWithShot; i < (int)Sequences::Count; i++) {
		animations.emplace_back(Animation(5 * obj.width, obj.height * (i - (int)Sequences::StandDownWithShot), obj.width, obj.height, 1, surface, 0.1f));
	}
}

Object Player::getObject()
{
	return object;
}
