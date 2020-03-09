#ifndef __PLAYER_H__
#define __PLAYER_H__
#include "Module.h"
#include "Globals.h"
#include "Animation.h"

enum xSTATE {
	xIDLE, xDAMAGED, xDEAD, xSHOOTING
};

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
	void Damage(int damage);

	//Animations
	Animation normal_anim;
	Animation shooting_anim;
	Animation damage_anim;
	Animation dead_anim;
	Animation kamehameha;
	Animation* curr_anim;

	xSTATE curr_state = xIDLE;

	SDL_Texture* texture = nullptr;
	iPoint pos;

	int life = 100;
};
#endif // !__PLAYER_H__