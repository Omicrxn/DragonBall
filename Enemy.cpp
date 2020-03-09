#include "Globals.h"
#include "Game.h"
#include "TextureManager.h"
#include "Input.h"
#include "Render.h"
#include "ShootingEnemy.h"
#include "Transition.h"
#include "Menu.h"
#include "Enemy.h"
#include <iostream>
#include "Audio.h"

Enemy::Enemy() {
	//normal animation
	for (int i = 0; i < 4; i++)
	{
		normal_anim.PushBack({ 70 * i,0,70,70 });
	}
	normal_anim.speed = 0.035f;
	//SHOOTING ANIM
	
		shooting_anim.PushBack({ 140,210,70,70 });
	
	shooting_anim.speed = 0.05f;


	//DEAD ANIM
	for (int i = 5; i >= 0; i--)
	{
		dead_anim.PushBack({ 70 * i,140,70,70 });
	}
	dead_anim.speed = 0.05;
	dead_anim.loop = false;


	//damage anim
	damage_anim.PushBack({ 70 * 4,140,70,70 });
	damage_anim.speed = 0.03f;
	damage_anim.loop = false;

}


Enemy::~Enemy() {

}

bool Enemy::Init() {
	
	return true;
}

bool Enemy::Start() {

	life = 100;
	curr_state = IDLE;
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
int otra = 0;

update_status Enemy::Update() {
	update_status status = UPDATE_CONTINUE;
	int shoot = rand() % (40 - 0 + 1);
	if (life == 0) {
		curr_state = DEAD;
		if (curr_anim != &dead_anim) {
			curr_anim = &dead_anim;
			dead_anim.Reset();
		}
		gGame->transition->TransitionStart(this, gGame->menu);
	}
	

	if (curr_state == IDLE || curr_state == SHOOTING) {
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
	}


	if (shoot == 3 && curr_state != DEAD && curr_state != DAMAGED) {
		curr_state = SHOOTING;
		gGame->shootingEnemy->AddBullet(gGame->shootingEnemy->energyBull, pos.x - 10, (int)pos.y, 2);
		gGame->audio->PlayFx(gGame->audio->LoadFx("Assets/frieza_shoot.wav"));
		otra = 0;
	}
	else if (otra == 50 && curr_state != DEAD){
		curr_state = IDLE;
	}
	otra++;

	//STATE MACHINE
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
			SDL_Delay(100);
			curr_state = IDLE;
			damage_anim.Reset();
		}
		break;
	case DEAD:
		if (curr_anim != &dead_anim) {
			curr_anim = &dead_anim;
			dead_anim.Reset();
		}

		break;

	case SHOOTING:
		//shooting
		if (curr_anim != &shooting_anim) {
			curr_anim = &shooting_anim;
			shooting_anim.Reset();
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
	
	
	std::cout << "Enemy: " << life << std::endl;
}

// Unload assets
bool Enemy::CleanUp()
{
	LOG("Unloading player");
	return true;
}