#include "Sharprshooter.h"



void Sharpshooter::calculatePossibleShot(bool aimsRight, bool aimsLeft, bool aimsDown, bool aimsUp, const Vec2D& pos) //pos of player
{
	if (aimsDown) {
		for (int i = 0; i < distance; i++) {
			if (pos.y + i < Graphics::ScreenHeight)
				possibleShot.push_back({ pos.x - 9,pos.y + i });
			else { break; }
		}
	}
	else if (aimsRight) {
		for (int i = 0; i < distance; i++) {
			if (pos.x + i < Graphics::ScreenWidth)
				possibleShot.push_back({ pos.x + 9 + i,pos.y - 2 });
			else { break; }
		}
	}
	else if (aimsLeft) {
		for (int i = 0; i < distance; i++) {
			if (pos.x - i > 0)
				possibleShot.push_back({ pos.x - 9 - i,pos.y - 2 });
			else { break; }
		}
	}
	else if (aimsUp) {
		for (int i = 0; i < distance; i++) {
			if (pos.y - i > 0)
				possibleShot.push_back({ pos.x + 9,pos.y - i });
			else { break; }
		}
	}

}

bool Compare_distanceUzi(std::unique_ptr<Enemy>& obj1, std::unique_ptr<Enemy>& obj2) {
	if (obj1 && obj2)
		return obj1->distance < obj2->distance;

	return true;
}

bool Compare_distanceUzi2(Obstacle obj1, Obstacle obj2) {
	return obj1.distance < obj2.distance;
}
bool  Sharpshooter::Shoot(bool aimsRight, bool aimsLeft, bool aimsDown, bool aimsUp, std::vector<std::unique_ptr<Enemy>>& enemy, std::vector<Obstacle>obstacles, const Vec2D& pos, float dt, bool isMoving)
{
	currentTime += dt;
	if (currentTime >= holdTime && ammo > 0) {
		currentTime = 0;
		ammo--;
		calculatePossibleShot(aimsRight, aimsLeft, aimsDown, aimsUp, pos);
		std::vector<std::unique_ptr<Enemy>> avaliableTarget; //tu mo¿e byæ problem
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
		std::sort(avaliableTarget.begin(), avaliableTarget.end(), Compare_distanceUzi);
		std::sort(availableObstacle.begin(), availableObstacle.end(), Compare_distanceUzi2);
		if (!avaliableTarget.empty() && availableObstacle.empty()) {
			int hittedTarget = 0;
			int copyofrof = 0;
				for (hittedTarget=0; hittedTarget < rof; hittedTarget++) {
					if (avaliableTarget.size() - 1 >= hittedTarget) {
						avaliableTarget[hittedTarget]->Hitted(damage);
						avaliableTarget[hittedTarget]->isHitted = true;
						copyofrof = hittedTarget;
					}
				}
			MakeCalculationoOfShot(avaliableTarget[copyofrof]->GetObjectW(), aimsRight, aimsLeft, aimsDown, aimsUp);
		}
		else if (!avaliableTarget.empty() && !availableObstacle.empty()) {
			if (availableObstacle[0].distance < avaliableTarget[0]->distance) { MakeCalculationoOfShot(availableObstacle[0].getObject(), aimsRight, aimsLeft, aimsDown, aimsUp); }
			else {
				int hittedTarget = 0;
				int copyofrof = rof;
				for (hittedTarget=0; hittedTarget < rof; hittedTarget++) {
					if (avaliableTarget.size() - 1 >= hittedTarget) {
						avaliableTarget[hittedTarget]->Hitted(damage);
						avaliableTarget[hittedTarget]->isHitted = true;
						copyofrof = hittedTarget;
					}
				}
				MakeCalculationoOfShot(avaliableTarget[copyofrof]->GetObjectW(), aimsRight, aimsLeft, aimsDown, aimsUp);
			}
		}
		else if (avaliableTarget.empty() && !availableObstacle.empty())MakeCalculationoOfShot(availableObstacle[0].getObject(), aimsRight, aimsLeft, aimsDown, aimsUp);
		//RemoveEnemiesFromVector(avaliableTarget);
		MergeVector(avaliableTarget, enemy);
		return true;
	}
	else {
		return false;
	}
}


void  Sharpshooter::CleanVector() {
	while (!possibleShot.empty())
		possibleShot.pop_back();
}

bool  Sharpshooter::CheckIfEnemyCanBeHitted(std::unique_ptr<Enemy>& enemy)
{
	Object obj = enemy->GetObjectW();
	for (int i = 0; i < possibleShot.size(); i++) {
		if (possibleShot[i].x > obj.hitbox.left && possibleShot[i].x < obj.hitbox.right && possibleShot[i].y < obj.hitbox.bottom && possibleShot[i].y > obj.hitbox.top) return true;
	}
	// return right > other.left && left < other.right&& bottom > other.top && top < other.bottom;
	return false;
}

bool  Sharpshooter::DrawShot(Graphics& gfx, float dt)
{
	currentTimeOfAnimation += dt;
	if (currentTimeOfAnimation <= holdTimeOfAnimation) {
		gfx.DrawUzi(possibleShot);
		return true;
	}
	else {
		currentTimeOfAnimation -= holdTimeOfAnimation;
		CleanVector();
		return false;
	}
}
void Sharpshooter::RemoveEnemiesFromVector(std::vector<std::unique_ptr<Enemy>>& enemies)
{
	enemies.clear();
}
bool  Sharpshooter::CheckIfObstacleCanBeHitted(Obstacle obstacle)
{
	Object obj = obstacle.getObject();
	for (int i = 0; i < possibleShot.size(); i++) {
		if (possibleShot[i].x > obj.hitbox.left && possibleShot[i].x < obj.hitbox.right && possibleShot[i].y < obj.hitbox.bottom && possibleShot[i].y > obj.hitbox.top) return true;
	}
	return false;
}

void  Sharpshooter::MakeCalculationoOfShot(const Object& obj, bool aimsRight, bool aimsLeft, bool aimsDown, bool aimsUp)
{

	if (aimsRight) {
		for (int i = possibleShot.size() - 1; i > 0; i--) {
			if (obj.hitbox.left < possibleShot[i].x)
			{
				possibleShot.pop_back();

			}
			else { break; }
		}
	}
	else if (aimsLeft) {
		for (int i = possibleShot.size() - 1; i > 0; i--) {
			if (obj.hitbox.right > possibleShot[i].x)
			{
				possibleShot.pop_back();

			}
			else { break; }
		}
	}
	else if (aimsDown) {
		for (int i = possibleShot.size() - 1; i > 0; i--) {
			if (obj.hitbox.top < possibleShot[i].y)
			{
				possibleShot.pop_back();

			}
			else { break; }
		}
	}
	else if (aimsUp) {
		for (int i = possibleShot.size() - 1; i > 0; i--) {
			if (obj.hitbox.bottom > possibleShot[i].y)
			{
				possibleShot.pop_back();

			}
			else { break; }
		}
	}
}

void Sharpshooter::MergeVector(std::vector<std::unique_ptr<Enemy>>& avaliableTarget, std::vector<std::unique_ptr<Enemy>>& enemy)
{
	enemy.erase(std::remove_if(enemy.begin(), enemy.end(), [](std::unique_ptr<Enemy>& e) {if (e)return !e->IsAlive(); else return true; }), enemy.end());
	for (auto & e : avaliableTarget) {
		if (e != nullptr) {
			enemy.push_back(std::move(e));
			std::sort(enemy.begin(), enemy.end(), Compare_distanceUzi);
		}
	}

}

void Sharpshooter::AddAmo(int amo)
{
	ammo += amo;
}

