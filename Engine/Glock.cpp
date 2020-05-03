#include "Glock.h"
#include "Object.h"
#include "Enemy.h"

void Glock::calculatePossibleShot(bool aimsRight, bool aimsLeft, bool aimsDown, bool aimsUp,const Vec2D & pos) //pos of player
{
	if (aimsDown){
		for (int i = 0; i < distance; i++) {
			if(pos.y + i<Graphics::ScreenHeight)
			possibleShot[i] = { pos.x,pos.y + i};
			else { break; }
	}
	}
	else if (aimsRight){
		for (int i = 0; i < distance; i++) {
			if (pos.x + i < Graphics::ScreenWidth)
				possibleShot[i] = { pos.x + i,pos.y  };
			else { break; }
		}
	}
	else if (aimsLeft){
		for (int i = 0; i < distance; i++) {
			if (pos.x - i > 0)
				possibleShot[i] = { pos.x - i,pos.y };
			else { break; }
		}
	}
	else if (aimsUp){
		for (int i = 0; i <distance; i++) {
			if (pos.y - i>0)
				possibleShot[i] = { pos.x,pos.y-i };
			else { break; }
		}
	}
	
}
bool compare_distance(Enemy * obj1 , Enemy * obj2){
	return obj1->distance < obj2->distance;
}

void Glock::Shoot(bool aimsRight, bool aimsLeft, bool aimsDown, bool aimsUp,std::vector<Enemy*> enemy, const Vec2D& pos)
{
	calculatePossibleShot(aimsRight, aimsLeft, aimsDown, aimsDown, pos);
	std::vector<Enemy*> avaliableTarget;
	
	int numberousOfEnemy = enemy.size();
	for (int i = 0; i < numberousOfEnemy; i++) {
		if (CheckIfEnemyCanBeHitted(enemy[i])) {
			enemy[i]->CalculateDistance(pos);
			avaliableTarget.push_back(enemy[i]); }
		else {
			enemy[i]->distance = INFINITE;
		}
	}
	std::stable_sort(avaliableTarget.begin(), avaliableTarget.end(), compare_distance);
}

bool Glock::CheckIfEnemyCanBeHitted(const Enemy* enemy)
{
	for (int i = 0; i < possibleShot.size(); i++) {
		Object obj = enemy->Getobject();
		if (possibleShot[i].x > obj.hitbox.left && possibleShot[i].x < obj.hitbox.right && possibleShot[i].y<obj.hitbox.bottom && possibleShot[i].y > obj.hitbox.top) return true;	
	}
	return false;
}