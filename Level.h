#pragma once
#ifndef __ModuleSceneForest_H__
#define __ModuleSceneForest_H__
#include "Module.h"
#include "Globals.h"
class Level : public Module {

public:
	Level();
	~Level();

	bool Start();
	update_status Update();
	bool CleanUp();
	

private:
	SDL_Rect src;
	SDL_Texture* texture;
};




#endif