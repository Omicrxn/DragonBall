#include "Globals.h"
#include "Game.h"
#include "TextureManager.h"
#include "Input.h"
#include "Render.h"
#include "Enemy.h"
#include <iostream>

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

	
		damage_anim.PushBack({ 70 * 4,140,70,70 });

	damage_anim.speed = 0.001f;

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
	texture = gGame->textures->Load("Assets/FREEZER_SPRITESHEET_INVERTED.png");
	if (texture == nullptr) {
		ret = false;
	}
	pos.x = initialX;

	return ret;
}

int num = 18;

update_status Enemy::Update() {
	update_status status = UPDATE_CONTINUE;

	//Idle handle
	
	if (pos.y <= 0)
	{
		num = 18;
	}
	if (num > 0 && pos.y > SCREEN_HEIGHT / 2)
	{
		num = 5;
	}
	else if (num < 0 && pos.y < SCREEN_HEIGHT / 2)
	{
		num = -5;
	}
	if (pos.y >= SCREEN_HEIGHT - 125)
	{
		num = -18;
	}
	pos.y += num;

	switch (curr_state) {
	case IDLE:
		if (curr_anim != &normal_anim) {
			curr_anim = &normal_anim;
			normal_anim.Reset();
		}
		break;
	case DAMAGED:
		if (curr_anim != &damage_anim) {
			curr_anim = &damage_anim;
			damage_anim.Reset();
		}
		break;
	}

	SDL_Rect rect = curr_anim->GetCurrentFrame();
	if (!gGame->render->Blit(texture, pos.x, pos.y, &rect, false)) {
		LOG("Cannot blit the texture in ModulePlayer %s\n", SDL_GetError());
		status = UPDATE_ERROR;
	}
	return status;
}

int Enemy::getLife() {
	return life;
}
void Enemy::Damage(int damage) {
	curr_state = DAMAGED;
	life -= damage;
	if (life <= 0) {
		life = 0;
	}
}

// Unload assets
bool Enemy::CleanUp()
{
	LOG("Unloading player");
	return true;
}