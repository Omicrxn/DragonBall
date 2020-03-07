
#include "Globals.h"
#include "Game.h"
#include "Render.h"
#include "Level.h"
#include "TextureManager.h"
#include "Audio.h"

Level::Level() {


}

Level::~Level() {

}


bool Level::Start() {
	bool ret = true;

	gGame->audio->PlayMusic("Assets/ost.mp3");
	texture = gGame->textures->Load("Assets/background.jpg");
	if (texture == nullptr) {
		ret = false;
	}

	src.w = 1750;
	src.h = 1750;
	src.x = src.y = 0;
	return ret;
}

update_status Level::Update() {
	update_status status = UPDATE_CONTINUE;
	if (!gGame->render->Blit(texture, 0, 0, &src,true)) {
		LOG("Cannot blit the texture in ModulePlayer %s\n", SDL_GetError());
		status = UPDATE_ERROR;
	}

	return status;
}

bool Level::CleanUp()
{
	LOG("Unloading SceneForest");
	gGame->audio->Disable();
	bool ret = true;

	return ret;
}