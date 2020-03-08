#pragma once
#ifndef __Shooting_h__
#define __Shooting_h__

#include "Shooting.h"
#include "Game.h"
#include "Animation.h"
#include "PointOperations.h"
#include "Module.h"
#include "SDL.h"

#define MAX_BULLETS 20
struct Bullet {

	Animation anim;
	iPoint position;
	iPoint speed;
	Uint32 spawnTime;
	int damage;

	Bullet();

	Bullet(const Bullet& bullet);
	~Bullet();
	bool Update();
};

class Shooting : public Module {
public:
	Shooting();
	~Shooting();

	bool Start();
	update_status Update();
	bool CleanUp();
	void AddBullet(const Bullet &bullet, int x,int y,Uint32 delay);
	
private:
	SDL_Texture* text = nullptr;
	Bullet* bullet_arr[MAX_BULLETS];
	int last_bullet = 0;
public:
	Bullet kamehameha;
	Bullet energyBull;

	bool enemy_touched;
};


#endif //__Shooting_h__

