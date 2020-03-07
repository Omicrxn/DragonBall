#pragma once

#ifndef __ModuleWindow_H__
#define __ModuleWindow_H__

#include "Module.h"

struct SDL_Window;
struct SDL_Surface;

class Window : public Module
{
public:

	Window();

	// Destructor
	virtual ~Window();

	// Called before quitting
	bool Init();

	// Called before quitting
	bool CleanUp();


public:
	//The window we'll be rendering to
	SDL_Window* sdl_window = nullptr;

	//The surface contained by the window
	SDL_Surface* screen_surface = nullptr;

	SDL_Surface* iconExe;
};

#endif // __ModuleWindow_H__

