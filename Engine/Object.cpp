#include "Object.h"
Object::HitBox::HitBox(float right, float left, float top, float bottom) :left(left), right(right), top(top), bottom(bottom) {}

Object::HitBox::HitBox(const HitBox& box):right(box.right),left(box.left),top(box.top),bottom(box.bottom)
{
}

bool Object::HitBox::IsOverLapping(const  HitBox& other)
{
	return right > other.left && left < other.right && bottom > other.top && top < other.bottom;
}

void Object::HitBox::DoActualization(const Vec2D& pos, float width, float height)
{
	right = pos.x + width / 2;
	left = pos.x - width / 2;
	top = pos.y - height / 2;
	bottom = pos.y + height / 2;
}

bool Object::HitBox::IsOverLappingForEnemies(const Vec2D & other)
{
	if (other.x > left && other.x<right && other.y>top && other.y < bottom)return true;
	else { return false; }
	
}

bool Object::IsOverLapping(const Object other,bool aimsRight,bool aimsLeft,bool aimsDown,bool aimsUp)
{
		if (this->hitbox.IsOverLapping(other.hitbox)) {
		if (aimsRight) { this->pos.x += other.hitbox.left - this->hitbox.right; }
		 else if (aimsLeft) { this->pos.x += other.hitbox.right - this->hitbox.left; }
		 if (aimsDown) { this->pos.y += other.hitbox.top - this->hitbox.bottom; }
		 else if (aimsUp) { this->pos.y += other.hitbox.bottom - this->hitbox.top; }
		hitbox.DoActualization(this->pos, width, height);
		return true;
		}
	else {
		return false;
	}
}

bool Object::IsOverLappingEnemy(const Object other)
{
	if (this->hitbox.IsOverLapping(other.hitbox)) {
		return true;
	}
	else {
		return false;
	}
}



void Object::Move(const Vec2D& mov)
{
	hitbox.DoActualization(pos, width, height);
	if(pos.x-width/2+mov.x>=0&&pos.x+width/2+mov.x<Graphics::ScreenWidth && pos.y-height/2+mov.y>=0&&pos.y+height/2+mov.y<Graphics::ScreenHeight)
	pos += mov;
	hitbox.DoActualization(pos, width, height);
}

Object::Object(Vec2D pos, Vec2D mov, float width, float height) :pos(pos), movement(mov), hitbox((pos.x + width / 2), (pos.x - width / 2), (pos.y - height / 2), (pos.y + height / 2)) {
	this->height = height;
	this->width = width;
}

Object::Object(const Object& obj):hitbox(obj.hitbox),pos(obj.pos),movement(obj.movement)
{
	height = obj.height;
	width = obj.width;
}
