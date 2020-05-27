#include "Weapon.h"
#include <string>
#include <numeric>
Weapon::Weapon(int neededPoints, float damage, float rof, float distance, float spread, int ammo,float holdTime, float holdTimeOfAnimation) : holdTimeOfAnimation(holdTimeOfAnimation), neededPoints(neededPoints), damage(damage), rof(rof), distance(distance), spread(spread), ammo(ammo),holdTime(holdTime){}

std::string Weapon::GetInformationAboutCurrentGun()
{
    const char * nameofweapon = typeid(*this).name();
    std::string convert="";
    int i = 0;
    bool space = false;
    while (nameofweapon[i] != '\0') {
        if (nameofweapon[i] == 32) {
            space = true;
        }
        if(space)
        convert.push_back(nameofweapon[i]);
        i++;
    }
    if(ammo==0)return convert + ":" + "0";
    else if(ammo == 10000)
	return convert + ":" +"INF";
    else
    return convert + ":" + std::to_string(ammo);
}


std::string Weapon::GetName()
{
    const char* nameofweapon = typeid(*this).name();
    std::string name = "";
    int i = 0;
    bool space = false;
    while (nameofweapon[i] != '\0') {
        if (nameofweapon[i] == 32) {
            space = true;
        }
        if (space)
            name.push_back(nameofweapon[i]);
        i++;
    }
    return name;
}
