#include "Globals.h"
#include "Game.h"
#include "TextureManager.h"
#include "Input.h"
#include "Render.h"
#include "Enemy.h"

Enemy::Enemy() {
	//normal animation
	for (int i = 0; i < 4; i++)
	{
		normal_anim.PushBack({ 70 * i,0,70,70 });
	}
	normal_anim.speed = 0.035f;

	for (int i = 0; i < 2; i++)
	{
		shooting_anim.PushBack({ 70 * i,70,70,70 });
	}
	shooting_anim.speed = 0.05f;
}

Enemy::~Enemy() {

}

bool Enemy::Init() {

	return true;
}

bool Enemy::Start() {


	//loading player Textures
	LOG("Loading player textures");
	bool ret = true;
	texture = gGame->textures->Load("Assets/FREEZER_SPRITESHEET.png");
	if (texture == nullptr) {
		ret = false;
	}
	pos.x = initialX;

	return ret;
}
update_status Enemy::Update() {
	update_status status = UPDATE_CONTINUE;

	//Idle handle
	if (gGame->input->keyboard[SDL_SCANCODE_D] == KEY_IDLE || gGame->input->keyboard[SDL_SCANCODE_A] == KEY_IDLE) {
		if (curr_anim != &normal_anim) {
			curr_anim = &normal_anim;
			normal_anim.Reset();
		}
	}
	if (gGame->input->keyboard[SDL_SCANCODE_D] == KEY_REPEAT && pos.x < SCREEN_WIDTH - 125) {
		pos.x += 5;
	}
	if (gGame->input->keyboard[SDL_SCANCODE_A] == KEY_REPEAT && pos.x > 0) {
		pos.x -= 5;
	}

	if (gGame->input->keyboard[SDL_SCANCODE_W] == KEY_REPEAT && pos.y > 0)
	{
		pos.y -= 5;
	}
	if (gGame->input->keyboard[SDL_SCANCODE_S] == KEY_REPEAT && pos.y < SCREEN_HEIGHT - 125)
	{
		pos.y += 5;
	}

	if (gGame->input->keyboard[SDL_SCANCODE_SPACE] == KEY_REPEAT) {
		if (curr_anim != &shooting_anim) {
			curr_anim = &shooting_anim;
			shooting_anim.Reset();
		}
	}

	SDL_Rect rect = curr_anim->GetCurrentFrame();
	if (!gGame->render->Blit(texture, pos.x, pos.y, &rect, false)) {
		LOG("Cannot blit the texture in ModulePlayer %s\n", SDL_GetError());
		status = UPDATE_ERROR;
	}
	return status;
}


// Unload assets
bool Enemy::CleanUp()
{
	LOG("Unloading player");
	return true;
}