#pragma once
#ifndef __GAME__H__
#define __GAME__H__

#include "Globals.h"
#include "Time.h"
#include "SDL_mixer.h"
#define NUM_MODULES 6 //number of modules created
//definition of all the modules created
class Window;
class Input;
class Render;
class Module;
class TextureManager;
class Player;
class Level;

class Game
{
public:
	Game();//constructor
	~Game();//deconstructor
	Mix_Music* backgroundSound;
	Module* modules[NUM_MODULES];//array of all modules
	//variables of all modules
	Window* window;
	Render* render;
	Input* input;
	Player* player;
	TextureManager* textures;
	Level* level;
	public:
	bool Init();//method to initialize everything
	update_status Update();//variable to update which returns update_status (globals.h)
	bool CleanUp();//method to clean everything
	
};

//To make it global and be able to access from other calses without include
extern Game* gGame;
#endif 