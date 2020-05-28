/******************************************************************************************
 *	Chili DirectX Framework Version 16.07.20											  *
 *	Game.cpp																			  *
 *	Copyright 2016 PlanetChili.net <http://www.planetchili.net>							  *
 *																						  *
 *	This file is part of The Chili DirectX Framework.									  *
 *																						  *
 *	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
 *	it under the terms of the GNU General Public License as published by				  *
 *	the Free Software Foundation, either version 3 of the License, or					  *
 *	(at your option) any later version.													  *
 *																						  *
 *	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
 *	GNU General Public License for more details.										  *
 *																						  *
 *	You should have received a copy of the GNU General Public License					  *
 *	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
 ******************************************************************************************/
#include "MainWindow.h"
#include "Game.h"




Game::Game(MainWindow& wnd)
	:
	wnd(wnd),
	gfx(wnd),
	frame(Vec2D(0, 0), Vec2D(0, 0), Graphics::ScreenWidth, Graphics::ScreenHeight),
	mov(0, 0),
	player(Object(Vec2D(56, 52), Vec2D(2, 2), 21, 40), 100, true, std::make_shared<Glock>()),
	board(1),
	game_over(L"Sounds\\game_over.wav"),
	glock_shooting(L"Sounds\\glock_shooting.wav"),
	uzi_shooting(L"Sounds\\uzi_shooting.wav"),
	zombie_attack(L"Sounds\\zombie_attack.wav"),
	zombie_dying(L"Sounds\\zombie_dying.wav"),
	bomber_attack(L"Sounds\\bomber_attack.wav"),
	box_collected(L"Sounds\\box_collected.wav"),
	change_weapon(L"Sounds\\change_weapon.wav"),
	player_getting_hit(L"Sounds\\player_getting_hit.wav")
{

	board.InitBoard();
}

void Game::Go()
{
	gfx.BeginFrame();
	UpdateModel();
	ComposeFrame();
	gfx.EndFrame();

}

void Game::UpdateModel()
{
	--changingWeapon;
	float clock = ft.Mark();
	board.SpawnEnemies(clock);
	board.AddNewBox(clock);
	board.ColectBox(player);
	std::vector<std::unique_ptr<Enemy>>& enemy = board.GetEnemies();
	float damageToPlayer = 0;
	float previousDamage = 0;
	int delay = 0;
	for (auto& opponent : enemy)
	{
		int enemyType = 0;
		enemyType = opponent->PreMovement(clock, player.getObject(), board.GetObstacles(), enemy, delay, damageToPlayer);

		if (enemyType == 1 && player.IsAlive()) {
			zombie_attack.Play(1.0, 0.8);
		}
		else if (enemyType == 2 && player.IsAlive()) {
			bomber_attack.Play(1.0, 2.0);
		}
		if (previousDamage != damageToPlayer)
		{
			delay += 20;
		}
		previousDamage = damageToPlayer;
	}

	if (damageToPlayer > 0 && player.IsAlive()) {
		player.ChangeHealth(damageToPlayer);
		player_getting_hit.Play(1.0, 3.0);
	}

	if (player.IsAlive()) {
		{
			if (wnd.kbd.KeyIsPressed(VK_UP)) { player.Movement(false, false, true, false, clock, board.GetObstacles(), enemy); }
			if (wnd.kbd.KeyIsPressed(VK_DOWN)) { player.Movement(false, false, false, true, clock, board.GetObstacles(), enemy); }
			if (wnd.kbd.KeyIsPressed(VK_RIGHT)) { player.Movement(true, false, false, false, clock, board.GetObstacles(), enemy); }
			if (wnd.kbd.KeyIsPressed(VK_LEFT)) { player.Movement(false, true, false, false, clock, board.GetObstacles(), enemy); }
			if (wnd.kbd.KeyIsEmpty()) { player.Movement(false, false, false, false, clock, board.GetObstacles(), enemy); }
		}
		if (wnd.kbd.KeyIsPressed(0x58) && changingWeapon <= 0) {
			changingWeapon = 40;
			if (player.ChangeGunForNextGun()) change_weapon.Play();
		}
		if (wnd.kbd.KeyIsPressed(0x5A) && changingWeapon <= 0) {
			changingWeapon = 40;
			if (player.ChangeGunForPreviousGun()) change_weapon.Play();
		}
		if (wnd.kbd.KeyIsPressed(VK_SPACE) && player.isShooting == false) {
			float clock2 = shotTime.Mark(); player.Shot(enemy, clock2, board.GetObstacles(), gfx);

			std::string weaponName = player.GetCurrentWeaponName();
			if (player.isShooting)
			{
				if (player.GetCurrentWeaponName() == " Glock") glock_shooting.Play(1.0, 0.3);
				else if (player.GetCurrentWeaponName() == " Uzi") uzi_shooting.Play(1.0, 0.2);
			}
		}
	}
	for (auto& e : enemy) {
		if (typeid(*e).hash_code() == typeid(Zombie).hash_code() && e->IsAlive() == false) {
			zombie_dying.Play();
		}
	}

	for (auto& e : enemy) {
		if (typeid(*e).hash_code() == typeid(Bomber).hash_code() && e->IsAlive() == false) {
			enemyToBoom.push_back(std::move(e));
		}
	}

	

	enemy.erase(std::remove_if(enemy.begin(), enemy.end(), [](std::unique_ptr<Enemy>& e)
		{
			if (e) {
				return !e->IsAlive();
			}
			else {
				return true;
			}
		})
		, enemy.end());
	mov = { 0.0,0.0 };
	board.DrawBoard(gfx);
	for (auto& opponent : enemy) {
		if (opponent)
			opponent->Draw(gfx);
	}
	player.Draw(gfx);
	enemyToBoom.erase(std::remove_if(enemyToBoom.begin(), enemyToBoom.end(), [](std::unique_ptr<Enemy>& e) {
		if (e) { return !e->IsAlive() && e->IfAnimationOver(); }
		else {
			return true;
		}})
		, enemyToBoom.end());
	for (auto& b : enemyToBoom) {
		if (b != nullptr)
			b->Boom(gfx, clock);
	}
	player.DrawShot(gfx, clock);

	enemyToBoom.erase(std::remove_if(enemyToBoom.begin(), enemyToBoom.end(), [](std::unique_ptr<Enemy>& e) {
		if (e) { return !e->IsAlive() && e->IfAnimationOver(); }
		else {
			return true;
		}})
		, enemyToBoom.end());
	fonte.DrawTexts(player.GetInformationAboutCurrentGun(), { 50.0f,750.0f }, Colors::Black, gfx);
	fonte.DrawTexts("Score:" + std::to_string(Points::GetPoints()), { 1050.0f,750.0f }, Colors::Black, gfx);
	board.NextRound(clock, gfx);
	board.LevelUp(player);
	if (!player.IsAlive()) {

		game_over.Play(0.2, 1.0);
		gfx.DrawSprite(100, 200, 1105, 624, Surface("Images\\GameOver.png", 1005, 424), Colors::MakeRGB(255, 255, 255));
		Sleep(100);



	}

	if (player.collectedBox)
	{
		box_collected.Play();
		player.collectedBox = false;
	}

}

void Game::ComposeFrame()
{
}