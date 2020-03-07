#include "Render.h"
#include "Globals.h"
#include "Game.h"
#include "Window.h"
#include "Input.h"
#include "SDL.h"

Render::Render() : Module()
{
	camera.x = camera.y = 0;
	camera.w = SCREEN_WIDTH;
	camera.h = SCREEN_HEIGHT;
}

// Destructor
Render::~Render()
{}

// Called before render is available
bool Render::Init()
{
	LOG("Creating Renderer context");
	bool ret = true;
	Uint32 flags = 0;

	if (REN_VSYNC == true)
	{
		flags |= SDL_RENDERER_PRESENTVSYNC;
	}

	renderer = SDL_CreateRenderer(gGame->window->sdl_window, -1, flags);

	SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH * SCREEN_SIZE, SCREEN_HEIGHT * SCREEN_SIZE);

	if (renderer == NULL)
	{
		LOG("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}

	return ret;
}

// Called every draw update
update_status Render::PreUpdate()
{
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderClear(renderer);

	return update_status::UPDATE_CONTINUE;
}

update_status Render::Update()
{

	return update_status::UPDATE_CONTINUE;
}

update_status Render::PostUpdate()
{
	SDL_RenderPresent(renderer);
	return update_status::UPDATE_CONTINUE;
}

// Called before quitting
bool Render::CleanUp()
{
	LOG("Destroying renderer");

	//Destroy window
	if (renderer != NULL)
	{
		SDL_DestroyRenderer(renderer);
	}

	return true;
}

// Blit to screen
bool Render::Blit(SDL_Texture* texture, int x, int y, SDL_Rect* section,bool background, float speed)
{
	bool ret = true;
	SDL_Rect rect;
	rect.x = (int)(camera.x * speed) + x * SCREEN_SIZE;
	rect.y = (int)(camera.y * speed) + y * SCREEN_SIZE;

	if (section != NULL)
	{
		rect.w = section->w;
		rect.h = section->h;
	}
	else
	{
		SDL_QueryTexture(texture, NULL, NULL, &rect.w, &rect.h);
	}

	if (background == true) {
		rect.w = SCREEN_WIDTH;
		rect.h = SCREEN_HEIGHT;
	}
	else {
		rect.w = 120;
		rect.h = 120;
	}
	

	if (SDL_RenderCopy(renderer, texture, section, &rect) != 0)
	{
		LOG("Cannot blit to screen. SDL_RenderCopy error: %s", SDL_GetError());
		ret = false;
	}

	return ret;
}

bool Render::DrawQuad(const SDL_Rect& rect, Uint8 r, Uint8 g, Uint8 b, Uint8 a, bool use_camera)
{
	bool ret = true;

	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(renderer, r, g, b, a);

	SDL_Rect rec(rect);
	if (use_camera)
	{
		rec.x = rect.x;
		rec.y = rect.y;
		/*rec.w *= SCREEN_SIZE;
		rec.h *= SCREEN_SIZE;*/
		rec.w = rect.w;
		rec.h = rect.h;
	}

	if (SDL_RenderFillRect(renderer, &rec) != 0)
	{
		LOG("Cannot draw quad to screen. SDL_RenderFillRect error: %s", SDL_GetError());
		ret = false;
	}

	return ret;
}