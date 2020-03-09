#include "ShootingEnemy.h"
#include "Player.h"
#include "TextureManager.h"
#include "Audio.h"
#include "Render.h"
#include "Enemy.h"

ShootingEnemy::ShootingEnemy() {
	energyBull.anim.PushBack({ 0,280,70,70 });

	energyBull.anim.speed = 1.0f;
	energyBull.speed.x = -10;

}

ShootingEnemy::~ShootingEnemy() {

}


bool ShootingEnemy::Start() {
	LOG("Loading particles");
	text = gGame->textures->Load("Assets/FREEZER_SPRITESHEET_INVERTED.png");
	
	return true;
}

// Unload assets
bool ShootingEnemy::CleanUp()
{

	LOG("Unloading particles");
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
update_status ShootingEnemy::Update()
{
	for (uint i = 0; i < MAX_BULLETS; ++i)
	{
		BulletEnemy* bullet = bullet_arr[i];

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
			gGame->render->Blit(text, bullet->position.x, bullet->position.y, &(bullet->anim.GetCurrentFrame()), false);
			if (bullet->chunk_played == false)
			{
				bullet->chunk_played = true;

			}
		}
		
		if (bullet->position.x == gGame->player->pos.x+120 && bullet->position.y >= gGame->player->pos.y && bullet->position.y <= gGame->player->pos.y + 120) {

			gGame->player->Damage(10);
		}
	}
	return UPDATE_CONTINUE;
}

void ShootingEnemy::AddBullet(const BulletEnemy& bullet, int x, int y, Uint32 delay)
{
	BulletEnemy* b = new BulletEnemy(bullet);
	b->spawnTime = SDL_GetTicks() + delay;
	b->position.x = x;
	b->position.y = y;



	bullet_arr[last_bullet++] = b;
	if (last_bullet == MAX_BULLETS)
		last_bullet = 0;
}

// -------------------------------------------------------------
// -------------------------------------------------------------

BulletEnemy::BulletEnemy()
{
	position.SetToZero();
	speed.SetToZero();
}

BulletEnemy::BulletEnemy(const BulletEnemy& b) :
	anim(b.anim), position(b.position), speed(b.speed), chunk(b.chunk),
	spawnTime(b.spawnTime), damage(b.damage)
{}

bool BulletEnemy::Update()
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

BulletEnemy::~BulletEnemy() {

}
