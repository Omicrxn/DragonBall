#ifndef __PLAYER_H__
#define __PLAYER_H__
#include "Module.h"
#include "Globals.h"
#include "Animation.h"

struct position {
	int x, y;
};
class Player : public Module
{
private:
	int initialX = 50, initialY = 50;
	position pos;
	bool isLeft;
	bool isUp;
public:
	Player();
	~Player();

	bool Init();
	bool Start();
	update_status Update();
	bool CleanUp();

	//Animations
	Animation normal_anim;
	Animation* curr_anim;

	SDL_Texture* texture = nullptr;
	

};
#endif // !__PLAYER_H__
