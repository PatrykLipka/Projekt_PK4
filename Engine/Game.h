/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.h																				  *
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
#pragma once

#include "Keyboard.h"
#include "Mouse.h"
#include "Graphics.h"
#include "Object.h"
#include "Player.h"
#include "Surface.h"
#include "Animation.h"
#include "FrameTimer.h"
#include "Board.h"
#include "Enemy.h"
#include "Zombie.h"
#include "Bomber.h"
#include "Weapon.h"
#include "Glock.h"
#include <algorithm>
#include <string>
#include <iostream>
#include <cctype>
#include <xmemory>
#include "Uzi.h"
#include "Font.h"
#include "Sound.h"
#include "Shotgun.h"
#include "Sharprshooter.h"
#include "Menu.h"
#include "ThirdMap.h"


class Game
{
public:
	Game( class MainWindow& wnd );
	Game( const Game& ) = delete;
	Game& operator=( const Game& ) = delete;
	void Go();
private:
	void UpdateModel();
	/********************************/
	/*  User Functions              */
	/********************************/
private:
	MainWindow & wnd;
	Graphics gfx;
    Object frame;
    Vec2D mov;
    Player player;
    FrameTimer ft;
    FrameTimer shotTime;
    std::vector<Object> vec;
    Board board;
    std::vector<std::unique_ptr<Enemy>> enemyToBoom;
    Font fonte=Font("Images\\Consolas13x24.png",416,72);
    Sound game_over;
    Sound glock_shooting;
    Sound uzi_shooting;
    Sound shotgun_shooting;
    Sound sniper_shooting;
    Sound zombie_attack;
    Sound zombie_dying;
    Sound bomber_attack;
    Sound box_collected;
    Sound change_weapon;
    Sound player_getting_hit;
    int changingWeapon = 30;
    Menu menu;
    
	/********************************/
	/*  User Variables              */
	/********************************/
};