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
    player(Object(Vec2D(56, 52), Vec2D(2, 2), 21, 40), 100, true, new Glock( 0,  49,  1,  150,  1, 1, 1.0f,0.1f)),
    board(1)
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
    std::vector<std::unique_ptr<Enemy>>& enemy=board.GetEnemies();
    for (auto & opponent : enemy) { opponent->PreMovement(clock, player.getObject(), board.GetObstacles(), enemy);}

    if (wnd.kbd.KeyIsPressed(VK_UP)) { player.Movement(false, false, true, false, clock,board.GetObstacles(), enemy); }
    if (wnd.kbd.KeyIsPressed(VK_DOWN)) { player.Movement(false, false, false, true, clock, board.GetObstacles(), enemy); }
    if (wnd.kbd.KeyIsPressed(VK_RIGHT)) { player.Movement(true, false, false, false, clock, board.GetObstacles(), enemy); }
    if (wnd.kbd.KeyIsPressed(VK_LEFT)) { player.Movement(false, true, false, false, clock, board.GetObstacles(), enemy); }
    if (wnd.kbd.KeyIsEmpty()) {  player.Movement(false, false, false, false, clock, board.GetObstacles(), enemy); }
    if (wnd.kbd.KeyIsPressed(VK_SPACE)&&player.isShooting==false) { 
        float clock2 = shotTime.Mark();
        player.Shot(enemy,clock2, board.GetObstacles(),gfx); 
    }
    enemy.erase(std::remove_if(enemy.begin(), enemy.end(), [](std::unique_ptr<Enemy>& e) {if (e)return !e->IsAlive(); else return true;}), enemy.end());
    mov = { 0.0,0.0 }; 

    board.DrawBoard(gfx);
     for (auto & opponent : enemy) {
         opponent->Draw(gfx);
     }
     player.Draw(gfx);
     player.DrawShot(gfx, clock);
     if(board.GetEnemies().empty())
     board.NextRound();
}

void Game::ComposeFrame()
{
    //float clock;
    

  
}