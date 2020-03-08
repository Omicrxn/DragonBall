#pragma once
#ifndef __ENEMY_H__
#define __ENEMY_H__
#include "Module.h"
#include "Globals.h"
#include "Animation.h"

class Enemy : public Module
{
private:
	int initialX = 200, initialY = 50;
public:
	Enemy();
	~Enemy();

	bool Init();
	bool Start();
	update_status Update();
	bool CleanUp();

	//Animations
	Animation normal_anim;
	Animation shooting_anim;
	Animation* curr_anim;

	SDL_Texture* texture = nullptr;
	iPoint pos;

};
#endif // !__ENEMY_H__