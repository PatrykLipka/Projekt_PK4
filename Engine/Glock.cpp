#include "Glock.h"

void Glock::calculatePossibleShot(bool aimsRight, bool aimsLeft, bool aimsDown, bool aimsUp,const Vec2D & pos) //pos of player
{
	if (aimsDown){
		for (int i = 0; i < distance; i++) {
			if(pos.y + i<Graphics::ScreenHeight)
			possibleShot.push_back({pos.x,pos.y + i});
			else { break; }
	}
   	}
	else if (aimsRight){
		for (int i = 0; i < distance; i++) {
			if (pos.x + i < Graphics::ScreenWidth)
				possibleShot.push_back( { pos.x + i,pos.y  });
			else { break; }
		}
	}
	else if (aimsLeft){
		for (int i = 0; i < distance; i++) {
			if (pos.x - i > 0)
				possibleShot.push_back ( { pos.x - i,pos.y });
			else { break; }
		}
	}
	else if (aimsUp){
		for (int i = 0; i <distance; i++) {
			if (pos.y - i>0)
				possibleShot.push_back({ pos.x,pos.y-i });
			else { break; }
 		}
	}
	
}
bool compare_distance(Enemy * obj1 , Enemy * obj2){
	return obj1->distance < obj2->distance;
}
bool compare_distance2(Obstacle obj1, Obstacle obj2) {
	return obj1.distance < obj2.distance;
}


bool Glock::Shoot(bool aimsRight, bool aimsLeft, bool aimsDown, bool aimsUp,std::vector<Enemy*> enemy, std::vector<Obstacle>obstacles, const Vec2D& pos, float dt)
{
	currentTime += dt;
	if (currentTime >= holdTime) {

		currentTime -= holdTime;

		calculatePossibleShot(aimsRight, aimsLeft, aimsDown, aimsDown, pos);
		std::vector<Enemy*> avaliableTarget;
		std::vector<Obstacle> availableObstacle;
		int numberousOfEnemy = enemy.size();
		for (int i = 0; i < numberousOfEnemy; i++) {
			if (CheckIfEnemyCanBeHitted(enemy[i])) {
				enemy[i]->CalculateDistance(pos);
				avaliableTarget.push_back(enemy[i]);
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
		std::sort(avaliableTarget.begin(), avaliableTarget.end(), compare_distance);
		std::sort(availableObstacle.begin(), availableObstacle.end(), compare_distance2);
		
		if (!avaliableTarget.empty()&&availableObstacle.empty()) {

			avaliableTarget[0]->Hitted(damage);
			CleanVector();
			return true;
			//if(aimsRight)
		}
		else if (!avaliableTarget.empty() && !availableObstacle.empty()) {
			if(availableObstacle[0].distance<avaliableTarget[0]->distance){}
			else{
				avaliableTarget[0]->Hitted(damage);
				CleanVector();
				return true;
			}
		}
			return true;
	}
	return false;

}

void Glock::CleanVector() {
	while(!possibleShot.empty())
	possibleShot.pop_back();
}

bool Glock::CheckIfEnemyCanBeHitted(Enemy* enemy)
{	Object obj = enemy->GetObjectW();
	for (int i = 0; i < possibleShot.size(); i++) {
		if (possibleShot[i].x > obj.hitbox.left && possibleShot[i].x < obj.hitbox.right && possibleShot[i].y < obj.hitbox.bottom && possibleShot[i].y > obj.hitbox.top) return true;	
	}
	// return right > other.left && left < other.right&& bottom > other.top && top < other.bottom;
	return false;
}

void Glock::DrawShot(Graphics& gfx, bool aimsRight, bool aimsLeft, bool aimsDown, bool aimsUp,int distance,const Vec2D & pos)
{
	gfx.DrawGlock();
}

bool Glock::CheckIfObstacleCanBeHitted(Obstacle obstacle)
{
	Object obj = obstacle.getObject();
	for (int i = 0; i < possibleShot.size(); i++) {
		if (possibleShot[i].x > obj.hitbox.left && possibleShot[i].x < obj.hitbox.right && possibleShot[i].y < obj.hitbox.bottom && possibleShot[i].y > obj.hitbox.top) return true;
	}
	return false;
}

