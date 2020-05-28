#include "Shotgun.h"


Shotgun::Shotgun(int neededPoints, float damage, float rof, float distance, float spread, int ammo, float holdTime, float holdTimeOfAnimation) :Weapon(neededPoints, damage, rof, distance, spread, ammo, holdTime, holdTimeOfAnimation) {}

bool comparedistance(std::unique_ptr<Enemy>& obj1, std::unique_ptr<Enemy>& obj2) {
	if (obj1 && obj2)
		return obj1->distance < obj2->distance;

	return true;
}

bool comparedistance2(Obstacle obj1, Obstacle obj2) {
	return obj1.distance < obj2.distance;
}

bool Shotgun::Shoot(bool aimsRight, bool aimsLeft, bool aimsDown, bool aimsUp, std::vector<std::unique_ptr<Enemy>>& enemy, std::vector<Obstacle>obstacles, const Vec2D& pos, float dt)
{
	currentTime += dt;
	if (currentTime >= holdTime&&ammo>0) {
		currentTime = 0;
		ammo--;
		calculatePossibleShot(aimsRight, aimsLeft, aimsDown, aimsUp, pos);
		std::vector<std::unique_ptr<Enemy>> avaliableTarget; //tu mo�e by� problem
		std::vector<Obstacle> availableObstacle;
		int numberousOfEnemy = (int)enemy.size();
		for (int i = 0; i < numberousOfEnemy; i++) {
			if (CheckIfEnemyCanBeHitted(enemy[i])) {
				enemy[i]->CalculateDistance(pos);
				avaliableTarget.push_back(std::move(enemy[i]));
			}
			else {
				enemy[i]->distance = INFINITE;
			}
		}
		for (int i = 0; i < obstacles.size(); i++) {
			if (CheckIfObstacleCanBeHitted(obstacles[i])) {
				obstacles[i].CalculateDistance(pos);
				availableObstacle.push_back(obstacles[i]);
			}
		}
		std::sort(avaliableTarget.begin(), avaliableTarget.end(), comparedistance);
		std::sort(availableObstacle.begin(), availableObstacle.end(), comparedistance2);
		if (!avaliableTarget.empty() && availableObstacle.empty()) {
			avaliableTarget[0]->Hitted(damage);
			avaliableTarget[0]->isHitted = true;
			MakeCalculationoOfShot(avaliableTarget[0]->GetObjectW(), aimsRight, aimsLeft, aimsDown, aimsUp);
		}
		else if (!avaliableTarget.empty() && !availableObstacle.empty()) {
			if (availableObstacle[0].distance < avaliableTarget[0]->distance) { MakeCalculationoOfShot(availableObstacle[0].getObject(), aimsRight, aimsLeft, aimsDown, aimsUp); }
			else {
				avaliableTarget[0]->Hitted(damage);
				avaliableTarget[0]->isHitted = true;
				MakeCalculationoOfShot(avaliableTarget[0]->GetObjectW(), aimsRight, aimsLeft, aimsDown, aimsUp);
			}
		}
		else if (avaliableTarget.empty() && !availableObstacle.empty())MakeCalculationoOfShot(availableObstacle[0].getObject(), aimsRight, aimsLeft, aimsDown, aimsUp);
		MergeVector(avaliableTarget, enemy);
		return true;
	}
	else {
		return false;
	}
}

void Shotgun::CleanVector() {

	for (auto& vec : possibleShot) {
		vec.clear();
	}
	
}

bool Shotgun::CheckIfEnemyCanBeHitted(std::unique_ptr<Enemy>& enemy)
{
	for (auto vec : possibleShot) {//moze byc problem
		Object obj = enemy->GetObjectW();
		for (int i = 0; i < vec.size(); i++) {
			if (vec[i].x > obj.hitbox.left && vec[i].x < obj.hitbox.right && vec[i].y < obj.hitbox.bottom && vec[i].y > obj.hitbox.top) return true;
		}
		// return right > other.left && left < other.right&& bottom > other.top && top < other.bottom;
	}
	return false;
}

bool Shotgun::DrawShot(Graphics& gfx, float dt)
{
	currentTimeOfAnimation += dt;
	if (currentTimeOfAnimation <= holdTimeOfAnimation) {
		for(auto vec:possibleShot)
		gfx.DrawGlock(vec);
		return true;
	}
	else {
		currentTimeOfAnimation -= holdTimeOfAnimation;
		CleanVector();
		return false;
	}
}

bool Shotgun::CheckIfObstacleCanBeHitted(Obstacle obstacle)
{
	for (auto vec : possibleShot) { //moze byc problem 
		Object obj = obstacle.getObject();
		for (int i = 0; i < vec.size(); i++) {
			if (vec[i].x > obj.hitbox.left && vec[i].x < obj.hitbox.right && vec[i].y < obj.hitbox.bottom && vec[i].y > obj.hitbox.top) return true;
		}
	}
	return false;
}

void Shotgun::MakeCalculationoOfShot(const Object& obj, bool aimsRight, bool aimsLeft, bool aimsDown, bool aimsUp)
{
	for (auto & vec : possibleShot) {
		if (aimsRight) {
			for (int i = vec.size() - 1; i > 0; i--) {
				if (obj.hitbox.left < vec[i].x&&vec[i].y>obj.hitbox.top&&vec[i].y < obj.hitbox.bottom)
				{
					while(!(vec[i]==vec[vec.size()]))
					vec.pop_back();

				}
				
			}
		}
		else if (aimsLeft) {
			for (int i = vec.size() - 1; i > 0; i--) {
				if (obj.hitbox.right > vec[i].x&&vec[i].y > obj.hitbox.top && vec[i].y < obj.hitbox.bottom)
				{
					while (!(vec[i] == vec[vec.size()]))
						vec.pop_back();

				}
			
			}
		}
		else if (aimsDown) {
			for (int i = vec.size() - 1; i > 0; i--) {
				if (obj.hitbox.top < vec[i].y&&vec[i].x>obj.hitbox.left&& vec[i].x < obj.hitbox.right)
				{
					while (!(vec[i] == vec[vec.size()]))
						vec.pop_back();

				}
				
			}
		}
		else if (aimsUp) {
			for (int i = vec.size() - 1; i > 0; i--) {
				if (obj.hitbox.bottom > vec[i].y&& vec[i].x > obj.hitbox.left && vec[i].x < obj.hitbox.right)
				{
					while (!(vec[i] == vec[vec.size()]))
						vec.pop_back();
				}
			
			}
		}
	}
}


void Shotgun::MergeVector(std::vector<std::unique_ptr<Enemy>>& avaliableTarget, std::vector<std::unique_ptr<Enemy>>& enemy)
{
	enemy.erase(std::remove_if(enemy.begin(), enemy.end(), [](std::unique_ptr<Enemy>& e) {if (e)return !e->IsAlive(); else return true; }), enemy.end());
	for (auto& e : avaliableTarget) {
		enemy.push_back(std::move(e));
		std::sort(enemy.begin(), enemy.end(), comparedistance);
	}
}

void Shotgun::AddAmo(int amo)
{
	ammo += amo;
}

void Shotgun::calculatePossibleShot(bool aimsRight, bool aimsLeft, bool aimsDown, bool aimsUp, const Vec2D& pos) //pos of player
{
	std::vector<Vec2D>vec0;
	std::vector<Vec2D>vec1;
	std::vector<Vec2D>vec2;
	std::vector<Vec2D>vec3;
	std::vector<Vec2D>vec4;

	if (aimsDown) {
		for (int i = 0; i < distance; i++) {
			if (pos.y + i < Graphics::ScreenHeight) {
				vec0.push_back({ pos.x - 9,pos.y + i });
				vec1.push_back({ pos.x - 9 - (spread / 2) * i,pos.y + i });
				vec2.push_back({ pos.x - 9 + (spread / 2) * i,pos.y + i });
				if (spread == 1) {
				vec3.push_back({ pos.x - 9 - (spread) * i,pos.y + i }); vec4.push_back({ pos.x - 9 +(spread) * i,pos.y + i });
			}
			}
			
			else { break; }
		}
	}
	else if (aimsRight) {
		for (int i = 0; i < distance; i++) { 
			if (pos.x + i < Graphics::ScreenWidth) {
				vec0.push_back({ pos.x + 9 + i,pos.y - 2 });
				vec1.push_back({ pos.x + 9 + i,pos.y - 2 - (spread / 2) * i });
				vec2.push_back({ pos.x + 9 + i,pos.y - 2 + (spread / 2) * i });
			if (spread == 1){
				vec3.push_back({ pos.x + 9 + i,pos.y - 2 - (spread) * i });
				vec4.push_back({ pos.x + 9 + i,pos.y - 2 + (spread) * i });
			}}
			else { break; }
		}
	}
	else if (aimsLeft) {
		for (int i = 0; i < distance; i++) {
			if (pos.x - i > 0) {
				vec0.push_back({ pos.x - 9 - i,pos.y - 2 });
				vec1.push_back({ pos.x - 9 - i,pos.y - 2 - (spread / 2) * i });
				vec2.push_back({ pos.x - 9 - i,pos.y - 2 + (spread / 2) * i });
			if (spread == 1) {
				vec3.push_back({ pos.x - 9 - i,pos.y - 2 - (spread)*i });
				vec4.push_back({ pos.x - 9 - i,pos.y - 2 + (spread)*i });
			}}
			
			else { break; }
		}
	}
	else if (aimsUp) {
		for (int i = 0; i < distance; i++) {
			if (pos.y - i > 0) {
				vec0.push_back({ pos.x - 9,pos.y - i });
				vec1.push_back({ pos.x - 9 - (spread / 2) * i,pos.y - i });
				vec2.push_back({ pos.x - 9 + (spread / 2) * i,pos.y - i });
			if (spread == 1) {
				vec3.push_back({ pos.x - 9 - (spread)*i,pos.y - i }); vec4.push_back({ pos.x - 9 + (spread)*i,pos.y - i });
			}}
			
			else { break; }
		}
	}
	if (!vec0.size()==0)
		possibleShot.push_back(vec0);
	if (!vec1.size() == 0)
		possibleShot.push_back(vec1);
	if (!vec2.size() == 0)
		possibleShot.push_back(vec2);
	if (!vec3.size() == 0)
		possibleShot.push_back(vec3);
	if (!vec4.size() == 0)
		possibleShot.push_back(vec4);

}
