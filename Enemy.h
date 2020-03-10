#pragma once
#ifndef __ENEMY_H__
#define __ENEMY_H__
#include "Module.h"
#include "Globals.h"
#include "Animation.h"

enum STATE {
	IDLE, DAMAGED, DEAD,SHOOTING,STOP
};

class Enemy : public Module
{
private:
	int initialX = SCREEN_WIDTH-170, initialY = 50;
public:
	Enemy();
	~Enemy();

	bool Init();
	bool Start();
	update_status Update();
	bool CleanUp();
	int getLife();
	void Damage(int damage);

	//Animations
	Animation normal_anim;
	Animation shooting_anim;
	Animation damage_anim;
	Animation dead_anim;
	Animation* curr_anim;

	STATE curr_state = IDLE;

	SDL_Texture* texture = nullptr;
	iPoint pos;

	int life = 100;

};
#endif // !__ENEMY_H__