
#include "Globals.h"
#include "Game.h"
#include "Render.h"
#include "Level.h"
#include "TextureManager.h"

Level::Level() {


}

Level::~Level() {

}


bool Level::Start() {
	bool ret = true;

	//texture = gGame->textures->Load("Assets/Background.png");
	if (texture == nullptr) {
		ret = false;
	}

	src.w = 1200;
	src.h = 800;
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

	bool ret = true;

	return ret;
}