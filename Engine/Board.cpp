#include "Board.h"

Board::Board(int numberOfEnemiesInFirstRound):round(numberOfEnemiesInFirstRound)
{
	
	InitVectorOfWeapon();
}
void Board::LevelUp(Player& player)
{
	if (round.GetCurrentRound()==3&&allWeapons.size()!=0&& typeid(*allWeapons[0]) == typeid(Uzi)) {
  			player.SetNewOwnedGun(allWeapons[0]);
			allWeapons.erase(std::remove_if(allWeapons.begin(), allWeapons.end(), [](std::shared_ptr<Weapon> e) {if (typeid(*e) == typeid(Uzi))return true; else return false; }), allWeapons.end());
	}
	if (round.GetCurrentRound() == 6&& allWeapons.size() != 0&& typeid(*allWeapons[0]) == typeid(Shotgun)) {
			player.SetNewOwnedGun(allWeapons[0]);
			allWeapons.erase(std::remove_if(allWeapons.begin(), allWeapons.end(), [](std::shared_ptr<Weapon> e) {if (typeid(*e) == typeid(Shotgun))return true; else return false; }), allWeapons.end());
	}
	if (round.GetCurrentRound() == 8&& allWeapons.size() != 0&& typeid(*allWeapons[0]) == typeid(Sharpshooter)) {
			player.SetNewOwnedGun(allWeapons[0]);
			allWeapons.erase(std::remove_if(allWeapons.begin(), allWeapons.end(), [](std::shared_ptr<Weapon> e) {if (typeid(*e) == typeid(Sharpshooter))return true; else return false; }), allWeapons.end());
	}
	if (round.GetCurrentRound() == 7) {
		player.Upgrade(typeid(Glock).hash_code(), 1);
	}
	if (round.GetCurrentRound() == 9) {
		player.Upgrade(typeid(Uzi).hash_code(), 1);
	}
	if (round.GetCurrentRound() == 11) {
		player.Upgrade(typeid(Shotgun).hash_code(), 1);
	}
	if (round.GetCurrentRound() == 12) {
		player.Upgrade(typeid(Sharpshooter).hash_code(), 2);
	}
	if (round.GetCurrentRound() == 13) {
		player.Upgrade(typeid(Glock).hash_code(), 2);
	}
	if (round.GetCurrentRound() == 15) {
		player.Upgrade(typeid(Sharpshooter).hash_code(), 2);
	}
	if (round.GetCurrentRound() == 17) {
		player.Upgrade(typeid(Shotgun).hash_code(), 2);
	}
	if (round.GetCurrentRound() == 19) {
		player.Upgrade(typeid(Uzi).hash_code(), 2);
	}
	if (round.GetCurrentRound() == 21) {
		player.Upgrade(typeid(Sharpshooter).hash_code(), 3);
	}
	if (round.GetCurrentRound() == 23) {
		player.Upgrade(typeid(Sharpshooter).hash_code(), 4);
	}
}
void Board::InitBoard()
{
	map->InitMap();
}
void Board::DrawBoard(Graphics& gfx)
{
	map->DrawMap(gfx);
}

std::vector<Obstacle> Board::GetObstacles()
{
	return map->GetObstacles();
}
std::vector<std::unique_ptr<Enemy>>& Board::GetEnemies()
{
	return round.GetEnemies();
}

std::vector<Box> Board::GetBoxes()
{
	return map->GetBox();
}

void Board::SpawnEnemies(float dt)
{
	round.SpawnEnemy(dt);
}

void Board::NextRound(float dt,Graphics& gfx)
{
	round.NextRound(5,dt,gfx);
}



void Board::AddNewBox(float dt)
{
	map->AddNewBox(dt);
}

void Board::ColectBox(Player& player)
{
	std::vector<Box>& boxes = map->GetBox();
	for(auto & box:boxes){
		box.ColectBox(player);
	}
	boxes.erase(std::remove_if(boxes.begin(), boxes.end(), [](Box & b) {
			return b.AlreadyColected(); })
			, boxes.end());
}

void Board::LoadMap(std::shared_ptr<Map> mapa)
{
	this->map = mapa;
}

void Board::InitVectorOfWeapon()
{
	allWeapons.push_back(std::make_shared <Uzi>());
	allWeapons.push_back(std::make_shared<Shotgun>());
	allWeapons.push_back(std::make_shared<Sharpshooter>());
}




