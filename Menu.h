#pragma once

#ifndef __Menu_H__
#define __Menu_H__
#include "Game.h"
#include "Module.h"
#include "Animation.h"
#include "SDL.h"
class Menu : public Module
{
public:
	Menu();
	~Menu();
	bool Start();
	update_status Update();
	bool CleanUp();
	uint start_audio;
	SDL_Texture* texture = nullptr;
	Animation menu_anim;
};

#endif