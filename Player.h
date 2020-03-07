#ifndef __PLAYER_H__
#define __PLAYER_H__
#include "Module.h"
#include "Globals.h"

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

	SDL_Texture* texture = nullptr;
	SDL_Rect rect;
	SDL_Rect fire;

};
#endif // !__PLAYER_H__
