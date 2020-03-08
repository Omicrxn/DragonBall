#ifndef __PLAYER_H__
#define __PLAYER_H__
#include "Module.h"
#include "Globals.h"
#include "Animation.h"


class Player : public Module
{
private:
	int initialX = 50, initialY = 50;
public:
	Player();
	~Player();

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
#endif // !__PLAYER_H__