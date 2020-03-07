#include "Globals.h"
#include "Game.h"
#include "Window.h"
#include "SDL.h"

Window::Window() : Module()
{
}

// Destructor
Window::~Window()
{
}

// Called before render is available
bool Window::Init()
{
	LOG("Init SDL window & surface");
	bool ret = true;

	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMECONTROLLER) < 0)
	{
		LOG("SDL_VIDEO could not initialize! SDL_Error:\n");
		LOG(SDL_GetError());
		ret = false;
	}
	else
	{
		//TODO: UNCOMMENT TO CREATE THE ICON
		//iconExe = SDL_LoadBMP("Assets/UserInterface/icon.bmp");

		//Create window
		int width = SCREEN_WIDTH * SCREEN_SIZE;
		int height = SCREEN_HEIGHT * SCREEN_SIZE;

		Uint32 flags = SDL_WINDOW_SHOWN;

		if (WIN_FULLSCREEN == true)
			flags |= SDL_WINDOW_FULLSCREEN;

		if (WIN_BORDERLESS == true)
			flags |= SDL_WINDOW_BORDERLESS;

		if (WIN_RESIZABLE == true)
			flags |= SDL_WINDOW_RESIZABLE;

		if (WIN_FULLSCREEN_DESKTOP == true)
			flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;

		sdl_window = SDL_CreateWindow(WIN_TITLE, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, flags);

		SDL_SetWindowIcon(sdl_window, iconExe);

		if (sdl_window == NULL)
		{
			LOG("Window could not be created! SDL_Error: %s\n", SDL_GetError());
			ret = false;
		}
		else
		{
			//Get window surface
			screen_surface = SDL_GetWindowSurface(sdl_window);
		}
	}



	return ret;
}

// Called before quitting
bool Window::CleanUp()
{
	LOG("Destroying SDL window and quitting all SDL systems");

	//Destroy window
	if (sdl_window != NULL)
		SDL_DestroyWindow(sdl_window);

	if (iconExe != NULL)
		SDL_FreeSurface(iconExe);

	//Quit SDL subsystems
	SDL_Quit();
	return true;
}