#pragma once
#ifndef __ModuleTextures_H__
#define __ModuleTextures_H__

#include "Module.h"
#include "Globals.h"

#define MAX_TEXTURES 200

struct SDL_Texture;
class TextureManager : public Module
{
public:
	TextureManager();
	~TextureManager();

	bool Init();
	bool CleanUp();

	SDL_Texture* const Load(const char* path);
	bool Unload(SDL_Texture* tex);
	void GetSize(const SDL_Texture* texture, uint& width, uint& height) const;

	SDL_Texture* textures[MAX_TEXTURES];
	uint last_texture = 0;
};

#endif // __ModuleTextures_H__