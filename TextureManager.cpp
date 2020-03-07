#include "TextureManager.h"
#include "Globals.h"
#include "Game.h"
#include "Render.h"
#include "SDL.h"
#include "SDL_image.h"

TextureManager::TextureManager() : Module() {
	for (uint i = 0; i < MAX_TEXTURES; i++)
	{
		textures[i] = nullptr;
	}
}

TextureManager::~TextureManager() {
}

bool TextureManager::Init() {
	LOG("Initializing Image Library");
	bool ret = true;

	//initializing PNG support
	int flags = IMG_INIT_PNG;
	int init = IMG_Init(flags);
	if ((init & flags) != flags) {
		LOG("There is an error initializing Img_Init: %s", IMG_GetError());
		ret = false;
	}
	return ret;
}

//Called before quitting
bool TextureManager::CleanUp() {
	LOG("Freeing textures and Image library");

	for (uint i = 0; i < MAX_TEXTURES; ++i)
		if (textures[i] != nullptr)
			SDL_DestroyTexture(textures[i]);

	IMG_Quit();
	return true;
}

//Load new texture form file path
SDL_Texture* const TextureManager::Load(const char* path) {

	SDL_Texture* texture = NULL;
	SDL_Surface* surface = IMG_Load(path);

	if (surface == NULL) {
		LOG("Could not load surface from given path: %s. IMG_Load: %s", path, IMG_GetError);
	}
	else {
		texture = SDL_CreateTextureFromSurface(gGame->render->renderer, surface);
		if (texture==NULL)
		{
			LOG("Unable to create texture from surface! SDL Error: %s\n", SDL_GetError());
		}
		else {
			textures[last_texture++] = texture;
			if (last_texture > MAX_TEXTURES) {
				last_texture = 0;
			}
		}
		SDL_FreeSurface(surface);
		

	}
	return texture;
}

bool TextureManager::Unload(SDL_Texture* texture) {
	bool ret = false;

	for (uint i = 0; i < MAX_TEXTURES; ++i) {
		if (texture == textures[i]) {

			SDL_DestroyTexture(textures[i]);
			textures[i] = nullptr;
			ret = true;
			break;

		}
	}
	return ret;

}

// Retrieve size of a texture
void TextureManager::GetSize(const SDL_Texture* texture, uint& width, uint& height) const
{
	SDL_QueryTexture((SDL_Texture*)texture, NULL, NULL, (int*)&width, (int*)&height);
}