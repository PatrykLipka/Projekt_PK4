#pragma once
#include "Object.h"
#include "Keyboard.h"
#include "Graphics.h"
#include "Mouse.h"
#include "Crate.h"
#include <list>
#include <vector>
#include "Surface.h"
#include "Animation.h"
class Player
{	
	enum class Sequences {
		WalkingDown,
		WalkingUp,
		WalkingRight,
		WalkingLeft,
		StandDown,
		StandUp,
		StandRight,
		StandLeft,
		Count
	};
	float health;
	bool isAlive;
	bool aimsRight;
	bool aimsLeft;
	bool aimsDown;
	bool aimsUp;
	Object object;
	Sequences iCurrentSeqence = Sequences::StandDown;
	std::vector<Animation>animations;
	Surface surface = Surface("Player1.png", 160, 192);
	std::vector<Vec2D> canBeHit;
	public:
	Player(Object obj, float hel,bool isAlive);
	Object getObject();
	void Movement(bool aim_R, bool aim_L, bool aim_U, bool aim_D,float dt);
	void CheckCollisions(std::vector<Object> obstacles); //po zaimplementowaniu klasy obstacle zmieniæ typ vektora
	//void CheckCrate(std::vector<Crate>& crates);
	void Draw( Graphics& gfx);
	void Update(float dt);
	
	
};

