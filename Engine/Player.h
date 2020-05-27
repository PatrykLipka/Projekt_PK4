#pragma once
#include "Enemy.h"
#include "Object.h"
#include "Keyboard.h"
#include "Graphics.h"
#include "Mouse.h"
#include "Crate.h"
#include <list>
#include <vector>
#include "Surface.h"
#include "Animation.h"
#include "Weapon.h"
#include "Obstacle.h"
#include "Uzi.h"
#include "Glock.h"

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
		WalkingDownWithShot,
		WalkingUpWithShot,
		WalkingRightWithShot,
		WalkingLeftWithShot,
		StandDownWithShot,
		StandUpWithShot,
		StandRightWithShot,
		StandLeftWithShot,
		Count
	};
	
	float health;
	bool isAlive = true;
	bool isHitted = false;
	bool aimsRight;
	bool aimsLeft;
	bool aimsDown;
	bool aimsUp;
	Object object;
	Sequences iCurrentSeqence = Sequences::StandDown;
	std::vector<Animation>animations;
	Surface surface = Surface("Images\\player_glock.png", 230, 164);
	std::vector <std::shared_ptr<Weapon>> ownedGuns;
	std::shared_ptr<Weapon> weapon;
	public:
	bool isShooting=false;
	bool collectedBox = false;
	Player(Object obj, float hel,bool isAlive,std::shared_ptr<Weapon> gun);
	Object getObject();
	void Movement(bool aim_R, bool aim_L, bool aim_U, bool aim_D,float dt,std::vector<Obstacle> obstacles, std::vector<std::unique_ptr<Enemy>>& enemies);
	void CheckCollisions(std::vector<Obstacle> obstacles); //po zaimplementowaniu klasy obstacle zmieniæ typ vektora
	bool CheckIfMovementPossible(std::vector<std::unique_ptr<Enemy>>& enemies, const Object& nextPosition);
	//void CheckCrate(std::vector<Crate>& crates);
	void Draw( Graphics& gfx);
	void Update(float dt);
	void Shot(std::vector<std::unique_ptr<Enemy>>& enemies, float dt,std::vector<Obstacle>obstacles,Graphics &gfx);
	void DrawShot(Graphics& gfx,float dt);
	void ChangeHealth(float changeHP);
	bool IsAlive();
	void SetNewOwnedGun(std::shared_ptr<Weapon> gun);
	int GetSizeOfOwnedGuns();
	void AddAmoTuGun(std::size_t hash_code,int amo);
	void Recover(float hp);
	bool ChangeGunForNextGun();
	bool ChangeGunForPreviousGun();
	std::string GetInformationAboutCurrentGun();
	std::string GetCurrentWeaponName();
};

