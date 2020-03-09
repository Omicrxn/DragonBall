#include "Shooting.h"
#include "Player.h"
#include "TextureManager.h"
#include "Audio.h"
#include "Enemy.h"
#include "Render.h"

Shooting::Shooting() {
		energyBull.anim.PushBack({ 0,70*3,70,70 });
		
	energyBull.anim.speed = 1.0f;
	energyBull.speed.x = 10;

	kamehameha.anim.PushBack({ 70,140,70,70 });
	kamehameha.anim.speed = 1.0f;
	kamehameha.speed.x = 10;
	
}

Shooting::~Shooting() {

}


bool Shooting::Start() {
	LOG("Loading particles");
	text = gGame->textures->Load("Assets/GOKU_SPRITESHEET.png");
	kamehameha.chunk = gGame->audio->LoadFx("Assets/kamehameha.wav");
	energyBull.chunk = gGame->audio->LoadFx("Assets/goku_shoot.wav");
	return true;
}

// Unload assets
bool Shooting::CleanUp()
{
	
	LOG("Unloading particles");
	gGame->audio->UnLoadFx(kamehameha.chunk);
	gGame->audio->UnLoadFx(energyBull.chunk);
	gGame->textures->Unload(text);
	text = nullptr;

	for (uint i = 0; i < MAX_BULLETS; ++i)
	{
		if (bullet_arr[i] != nullptr)
		{
			delete bullet_arr[i];
			bullet_arr[i] = nullptr;
		}
	}
	return true;
}

// Update: draw background
update_status Shooting::Update()
{
	for (uint i = 0; i < MAX_BULLETS; ++i)
	{
		Bullet* bullet = bullet_arr[i];

		if (bullet == nullptr)
			continue;

		if (bullet->position.y < -10 || bullet->position.y > SCREEN_WIDTH) {
			delete bullet;
			bullet_arr[i] = nullptr;
		}
		else if (bullet->Update() == false)
		{
			delete bullet;
			bullet_arr[i] = nullptr;
		}
		else if (SDL_GetTicks() >= bullet->spawnTime)
		{
			gGame->render->Blit(text, bullet->position.x, bullet->position.y, &(bullet->anim.GetCurrentFrame()),false);
			if (bullet->chunk_played == false)
			{
				bullet->chunk_played = true;
				
			}
		}

		if (bullet->position.x == gGame->enemy->pos.x && bullet->position.y >= gGame->enemy->pos.y - 50 && bullet->position.y <= gGame->enemy->pos.y + 50) {
			
			gGame->enemy->Damage(10);
		}
	}
	return UPDATE_CONTINUE;
}

void Shooting::AddBullet(const Bullet& bullet, int x, int y, Uint32 delay)
{
	Bullet* b = new Bullet(bullet);
	b->spawnTime = SDL_GetTicks() + delay;
	b->position.x = x;
	b->position.y = y;

	

	bullet_arr[last_bullet++] = b;
	if (last_bullet == MAX_BULLETS)
		last_bullet = 0;
}

// -------------------------------------------------------------
// -------------------------------------------------------------

Bullet::Bullet()
{
	position.SetToZero();
	speed.SetToZero();
}

Bullet::Bullet(const Bullet& b) :
	anim(b.anim), position(b.position), speed(b.speed), chunk(b.chunk),
	spawnTime(b.spawnTime), damage(b.damage)
{}

bool Bullet::Update()
{
	bool ret = true;


	if (damage > 0)
	{
		if ((SDL_GetTicks() - spawnTime) > damage)
			ret = false;
	}
	
	if (!SDL_GetTicks() - spawnTime > 0) {
		position.x += speed.x;
		position.y += speed.y;
	}

	

	return ret;
}

Bullet::~Bullet() {
	
}


