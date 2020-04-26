#include "Crate.h"

bool Crate::Collected(const Object& player)
{
	return object.hitbox.IsOverLapping(player.hitbox);
}