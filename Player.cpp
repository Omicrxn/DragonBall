#include "Globals.h"
#include "Game.h"
#include "TextureManager.h"
#include "Input.h"
#include "Render.h"
#include "Player.h"

Player::Player() {

}

Player::~Player() {

}

bool Player::Init() {
	
	return true;
}

bool Player::Start() {


	//loading player Textures
	LOG("Loading player textures");
	bool ret = true;
	//texture = gGame->textures->Load("Assets/Player.png");
	if (texture == nullptr) {
		ret = false;
	}
	rect.w = 400;
	rect.h = 400;
	rect.x = initialX;
	rect.y = initialY;

	return ret;
}
update_status Player::Update() {
	update_status status = UPDATE_CONTINUE;

	//Idle handle
	if (gGame->input->keyboard[SDL_SCANCODE_D] == KEY_IDLE || gGame->input->keyboard[SDL_SCANCODE_A] == KEY_IDLE) {
		
	}
     if (gGame->input->keyboard[SDL_SCANCODE_D] == KEY_REPEAT) {
		 pos.x += 10;
	}
	 if (gGame->input->keyboard[SDL_SCANCODE_A] == KEY_REPEAT ) {
		 pos.x -= 10;
	}

	 if (gGame->input->keyboard[SDL_SCANCODE_W] == KEY_REPEAT )
	 {
		 pos.y -=10;
	 }
	 if (gGame->input->keyboard[SDL_SCANCODE_S] == KEY_REPEAT )
	 {
		 pos.y += 10;
	 }

	 if (gGame->input->keyboard[SDL_SCANCODE_S] == KEY_REPEAT) {
	 }
	
	

	if (!gGame->render->Blit(texture,pos.x,pos.y,&rect,false)) {
		LOG("Cannot blit the texture in ModulePlayer %s\n", SDL_GetError());
		status = UPDATE_ERROR;
	}
	return status;
}


// Unload assets
bool Player::CleanUp()
{
	LOG("Unloading player");
	LOG("Unloading player Audio");
	//TODO: unload player Audio
	return true;
}