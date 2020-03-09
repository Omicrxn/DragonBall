#pragma once
#ifndef __ShootingEnemy_h__
#define __ShootingEnemy_h__

#include "Game.h"
#include "Animation.h"
#include "PointOperations.h"
#include "Module.h"
#include "SDL.h"

#define MAX_BULLETS 200
struct BulletEnemy {

	Animation anim;
	iPoint position;
	uint chunk = 0;
	bool chunk_played = false;
	iPoint speed;
	Uint32 spawnTime;
	Uint32 damage;

	BulletEnemy();

	BulletEnemy(const BulletEnemy& bullet);
	~BulletEnemy();
	bool Update();
};

class ShootingEnemy : public Module {
public:
	ShootingEnemy();
	~ShootingEnemy();

	bool Start();
	update_status Update();
	bool CleanUp();
	void AddBullet(const BulletEnemy& bullet, int x, int y, Uint32 delay);

private:
	SDL_Texture* text = nullptr;
	BulletEnemy* bullet_arr[MAX_BULLETS];
	int last_bullet = 0;
public:
	BulletEnemy energyBull;

	bool enemy_touched;
};


#endif //__ShootingEnemy_h__