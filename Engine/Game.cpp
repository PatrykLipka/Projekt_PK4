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
    player(Object(Vec2D(56, 52), Vec2D(2, 2), 21, 40), 100, true,std::make_shared<Glock>()),
    board(50),
    glock_shooting(L"Sounds\\glock_shooting.wav"),
    uzi_shooting(L"Sounds\\uzi_shooting.wav")
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
   
    float clock = ft.Mark();
    board.SpawnEnemies(clock);
    board.AddNewBox(clock);
    board.ColectBox(player);
    std::vector<std::unique_ptr<Enemy>>& enemy=board.GetEnemies();
    float damageToPlayer = 0;
    float previousDamage = 0;
    int delay=0;
    for (auto & opponent : enemy) 
    { 
        damageToPlayer+=opponent->PreMovement(clock, player.getObject(), board.GetObstacles(), enemy, delay);
        if (previousDamage!=damageToPlayer)
        {
            delay += 20;
        }
        previousDamage = damageToPlayer;
    }

    if (damageToPlayer > 0) {
        player.ChangeHealth(damageToPlayer);
    }

    if (player.IsAlive()) {
        {
            if (wnd.kbd.KeyIsPressed(VK_UP)) { player.Movement(false, false, true, false, clock, board.GetObstacles(), enemy); }
            if (wnd.kbd.KeyIsPressed(VK_DOWN)) { player.Movement(false, false, false, true, clock, board.GetObstacles(), enemy); }
            if (wnd.kbd.KeyIsPressed(VK_RIGHT)) { player.Movement(true, false, false, false, clock, board.GetObstacles(), enemy); }
            if (wnd.kbd.KeyIsPressed(VK_LEFT)) { player.Movement(false, true, false, false, clock, board.GetObstacles(), enemy); }
            if (wnd.kbd.KeyIsEmpty()) { player.Movement(false, false, false, false, clock, board.GetObstacles(), enemy); }
        }
         if (wnd.kbd.KeyIsPressed(0x58)) { player.ChangeGunForNextGun(); }
         if (wnd.kbd.KeyIsPressed(0x5A)) { player.ChangeGunForPreviousGun(); }
         if (wnd.kbd.KeyIsPressed(VK_SPACE)&&player.isShooting==false) { 
             float clock2 = shotTime.Mark(); player.Shot(enemy,clock2, board.GetObstacles(),gfx);
             std::string weaponName = player.GetCurrentWeaponName();
             if (player.isShooting)
             {
                 if (player.GetCurrentWeaponName() == " Glock") glock_shooting.Play();
                 else if (player.GetCurrentWeaponName() == " Uzi") uzi_shooting.Play();
             }
         }
    }
    for (auto& e : enemy) {
        if (typeid(*e).hash_code() == typeid(Bomber).hash_code() && e->IsAlive() == false) {
            enemyToBoom.push_back(std::move(e));
        }
    }
    enemy.erase(std::remove_if(enemy.begin(), enemy.end(), [](std::unique_ptr<Enemy>& e) {
        if (e) {return !e->IsAlive(); }
        else {
            return true;
        }})
        , enemy.end());
    mov = { 0.0,0.0 }; 
     board.DrawBoard(gfx);
     for (auto & opponent : enemy) {
         if(opponent)
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
         if (b!=nullptr)
          b->Boom(gfx, clock); 
     }
     player.DrawShot(gfx, clock);
    
     enemyToBoom.erase(std::remove_if(enemyToBoom.begin(), enemyToBoom.end(), [](std::unique_ptr<Enemy>& e) {
         if (e) { return !e->IsAlive()&&e->IfAnimationOver(); }
         else {
             return true;
         }})
         , enemyToBoom.end());
     fonte.DrawTexts(player.GetInformationAboutCurrentGun(), {50.0f,750.0f}, Colors::Black, gfx);
     board.LevelUp(player);
     if (!player.IsAlive()) {
       
         gfx.DrawSprite(100, 200, 1105, 624, Surface("GameOver.png", 1005, 424),Colors::MakeRGB(255,255,255));
         Sleep(100);
        // wnd.Kill();
         
     }
     
}

void Game::ComposeFrame()
{
    //float clock;
    

  
}