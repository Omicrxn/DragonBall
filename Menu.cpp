#include "Menu.h"
#include "Globals.h"
#include "Game.h"
#include "Input.h"
#include "TextureManager.h"
#include "Render.h"
#include "Audio.h"
#include "Menu.h"
#include "Transition.h"
#include "Level.h"

Menu::Menu()
{
	
	menu_anim.PushBack({ 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT});

}
Menu::~Menu()
{



}

bool Menu::Start()
{
	LOG("Loading welcome screen");
	bool ret = true;

	texture = gGame->textures->Load("assets/menu.png");
	if (texture == nullptr) {
		ret = false;
		LOG("Error loading the welcomeScreen spritesheet");
	}
	if (!gGame->audio->PlayMusic("Assets/ost.mp3"))
		ret = false;

	LOG("Loading audio fx for start");
	start_audio = gGame->audio->LoadFx("Assets/start.wav");

	return ret;
}

// Update: draw background
update_status Menu::Update()
{

	if ((gGame->input->keyboard[SDL_SCANCODE_RETURN] || gGame->input->keyboard[SDL_SCANCODE_SPACE])) {
		gGame->audio->PlayFx(start_audio);
		gGame->transition->TransitionStart(this, gGame->level);
	}

	update_status status = UPDATE_CONTINUE;

	if (!gGame->render->Blit(texture, 0, 0, &(menu_anim.GetCurrentFrame()), true))
		status = UPDATE_ERROR;

	return status;
}
bool Menu::CleanUp()
{
	//TODO check if we can control this
	LOG("Unloading welcome screen");

	gGame->audio->StopMusic();
	gGame->textures->Unload(texture);

	return true;
}