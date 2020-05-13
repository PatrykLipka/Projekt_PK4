#include "Weapon.h"

Weapon::Weapon(int neededPoints, float damage, float rof, float distance, float spread, int ammo,float holdTime, float holdTimeOfAnimation) : holdTimeOfAnimation(holdTimeOfAnimation), neededPoints(neededPoints), damage(damage), rof(rof), distance(distance), spread(spread), ammo(ammo),holdTime(holdTime){}
