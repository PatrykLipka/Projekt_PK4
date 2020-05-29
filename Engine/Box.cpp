#include "Box.h"

Box::Box(Object& obj) :object(obj) { alreadyColected = false; }

  Box::Box(Vec2D& pos, float width, float height) : object(pos, Vec2D(0, 0), width, height) { alreadyColected = false; }

bool Box::IsBoxCollected(const Object& player)
{
	return object.hitbox.IsOverLapping(player.hitbox);
}

void Box::ColectBox(Player & player)
{
	if (IsBoxCollected(player.getObject())) {
		this->alreadyColected = true;
		std::random_device device;
		std::mt19937 generator(device());
		
		std::uniform_int_distribution<int> distribution(1,player.GetSizeOfOwnedGuns());
		std::uniform_int_distribution<int> distributionAmo(10,40);
		
		
		int BonusNumber = distribution(generator);
		int amo = distributionAmo(generator);
		player.collectedBox = true;
		switch (BonusNumber) {
		case 1: 
			player.Recover(40.0f);
			break;
		case 2:
			player.AddAmoTuGun(typeid(Uzi).hash_code(), amo);
			break;
		case 3:
			player.AddAmoTuGun(typeid(Shotgun).hash_code(), amo);
			break;
		case 4:
			player.AddAmoTuGun(typeid(Sharpshooter).hash_code(), amo);
			break;

			
		}
	}
	
}

bool Box::AlreadyColected()
{
	return alreadyColected;
}

Object Box::getObject()
{
	return object;
}
