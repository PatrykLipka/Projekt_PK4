#include "Box.h"

bool Box::IsBoxCollected(const Object& player)
{
	return object.hitbox.IsOverLapping(player.hitbox);
}

void Box::ColectBox(Player& player)
{
	if (IsBoxCollected(player.getObject())) {
		alreadyColected = true;
		std::random_device device;
		std::mt19937 generator(device());
		std::uniform_int_distribution<int> distribution(1,player.GetSizeOfOwnedGuns()+1);
		std::uniform_int_distribution<int> distributionAmo(1, 20);
		int BonusNumber = distribution(generator);
		int amo = distributionAmo(generator);
		switch (BonusNumber) {
		case 1: 
			player.AddAmoTuGun(typeid(Uzi).hash_code(), amo);
			break;
		case 2:
			player.Recover(40.0f);
			break;
		}
	}
}

bool Box::AlreadyColected()
{
	return alreadyColected;
}
