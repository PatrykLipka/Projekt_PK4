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
    player(Object(Vec2D(28, 26), Vec2D(3, 3), 32, 48), 100, true),
    zombie(Object(Vec2D(100, 500), Vec2D(3, 3), 32, 48),100,50,true,5)
{

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
    if (wnd.kbd.KeyIsPressed(VK_UP)) { player.Movement(false, false, true, false, ft.Mark()); }
    if (wnd.kbd.KeyIsPressed(VK_DOWN)) { player.Movement(false, false, false, true, ft.Mark()); }
    if (wnd.kbd.KeyIsPressed(VK_RIGHT)) { player.Movement(true, false, false, false, ft.Mark()); }
    if (wnd.kbd.KeyIsPressed(VK_LEFT)) { player.Movement(false, true, false, false, ft.Mark()); }
    if (wnd.kbd.KeyIsEmpty()) { player.Movement(false, false, false, false, ft.Mark()); }

    player.CheckCollisions(vec);
    // player.Draw(gfx);
    mov = { 0.0,0.0 };
}

void Game::ComposeFrame()
{
     board.DrawBoard(gfx);
     zombie.Draw(gfx);
     player.Draw(gfx);
  
}