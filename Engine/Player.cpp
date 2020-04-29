#include "Player.h"

void Player::Movement(bool aim_R, bool aim_L, bool aim_U, bool aim_D,float dt)
{
	if (aim_R) {
		aimsRight=true;
		aimsLeft=false;
		aimsDown=false;
		aimsUp=false;
		iCurentSeqence = Sequences::WalkingRight;
		if((object.hitbox.right += object.movement.x) < Graphics::ScreenWidth - 1)
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
		iCurentSeqence = Sequences::WalkingLeft;
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
		iCurentSeqence = Sequences::WalkingUp;
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
		iCurentSeqence = Sequences::WalkingDown;
		if ((object.hitbox.bottom += object.movement.y) < Graphics::ScreenHeight - 1)
		object.pos.y += object.movement.y;
		else {
			float dy = Graphics::ScreenHeight - object.hitbox.bottom + object.movement.y;
			object.pos.y += dy;
		}
	
	}
	else {
		if (aim_D)iCurentSeqence = Sequences::StandDown;
		else if (aim_R)iCurentSeqence = Sequences::StandRight;
		else if (aim_L)iCurentSeqence = Sequences::StandLeft;
		else if (aim_U)iCurentSeqence = Sequences::StandUp;
	}
	object.hitbox.DoActualization(object.pos,object.width,object.height);
	Update(dt);
}

void Player::CheckCollisions(std::vector<Object> obstacles)
{
	for (auto obs : obstacles) {
		this->object.IsOverLapping(obs, aimsRight, aimsLeft, aimsDown, aimsUp);
	}
}

void Player::Draw( Graphics & gfx)
{
	Vec2D pos{ object.hitbox.left,object.hitbox.top };
	animations[(int)iCurentSeqence].Draw(pos, gfx);
}

void Player::Update(float dt)
{
	animations[(int)iCurentSeqence].Update(dt);
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

Player::Player(Object obj, float hel,bool isAlive):object(obj),health(hel),isAlive(isAlive)
{
	aimsRight = false;
	aimsLeft = false;
	aimsDown = true;
	aimsUp = false;
	for (int i = 0; i < (int)Sequences::StandDown; i++) {
		animations.emplace_back(Animation(32, 48 * i, 32, 48, 4, surface, 0.001f));
	}
	for (int i = (int)Sequences::StandDown; i < (int)Sequences::Count; i++) {
		animations.emplace_back(Animation(0, 48 * (i-(int)Sequences::StandDown), 32, 48, 1, surface, 0.001f));
	}
	
}
