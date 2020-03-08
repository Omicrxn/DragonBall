#pragma once
#ifndef __ENEMY_H__
#define __ENEMY_H__
#include "Module.h"
#include "Globals.h"
#include "Animation.h"

struct position {
	int x, y;
};
class Enemy : public Module
{
private:
	int initialX = 50, initialY = 50;
	position pos;
	bool isLeft;
	bool isUp;
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


};
#endif // !__ENEMY_H__

