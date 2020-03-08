#include "Shooting.h"
#include "Player.h"
#include "TextureManager.h"
#include "Render.h"
Shooting::Shooting() {
	for (int i = 0; i < 1; i++)
	{
		energyBull.anim.PushBack({ 70 * i,0,70,70 });
	}
	energyBull.anim.speed = 1.0f;
	energyBull.speed.x = 1;
	
}

Shooting::~Shooting() {

}


bool Shooting::Start() {
	LOG("Loading particles");
	text = gGame->textures->Load("Assets/GOKU_SPRITESHEET.png");

	return true;
}

// Unload assets
bool Shooting::CleanUp()
{
	

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

		if (bullet->position.y < -10 || bullet->position.y > SCREEN_HEIGHT&& bullet != &kamehameha) {
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
			//gGame->render->Blit(text, bullet->position.x, bullet->position.y, &(bullet->anim.GetCurrentFrame()));
			
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
	anim(b.anim), position(b.position), speed(b.speed),
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
	else
		if (anim.Finished())
			ret = false;

	if (!SDL_GetTicks() - spawnTime > 0) {
		position.x += speed.x;
		position.y += speed.y;
	}

	

	return ret;
}

Bullet::~Bullet() {
	
}


