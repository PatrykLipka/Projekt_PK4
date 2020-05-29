#include "Board.h"

Board::Board(int numberOfEnemiesInFirstRound):round(numberOfEnemiesInFirstRound)
{
	map = new SecondMap();
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
	round.NextRound(10,dt,gfx);
}

std::shared_ptr<Weapon>& Board::GetAvaliableGun()
{
	// TODO: tu wstawiæ instrukcjê return
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

void Board::InitVectorOfWeapon()
{
	allWeapons.push_back(std::make_shared <Uzi>());
	allWeapons.push_back(std::make_shared<Shotgun>());
	allWeapons.push_back(std::make_shared<Sharpshooter>());
}




