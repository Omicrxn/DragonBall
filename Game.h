#pragma once
#ifndef __GAME__H__
#define __GAME__H__

#include "Globals.h"
#include "Time.h"
#define NUM_MODULES 8 //number of modules created
//definition of all the modules created
class Window;
class Input;
class Render;
class Module;
class TextureManager;
class Enemy;
class Level;
class Audio;
class Enemy;

class Game
{
public:
	Game();//constructor
	~Game();//deconstructor
	Module* modules[NUM_MODULES];//array of all modules
	//variables of all modules
	Window* window;
	Render* render;
	Input* input;
	Enemy* player;
	TextureManager* textures;
	Level* level;
	Audio* audio;
	Enemy* enemy;
	public:
	bool Init();//method to initialize everything
	update_status Update();//variable to update which returns update_status (globals.h)
	bool CleanUp();//method to clean everything
	
};

//To make it global and be able to access from other calses without include
extern Game* gGame;
#endif 