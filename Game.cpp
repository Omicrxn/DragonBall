#include "Game.h"
#include "Window.h"
#include "Render.h"
#include "Input.h"
#include "TextureManager.h"
#include "Player.h"
#include "Level.h"

Game::Game() { //Constructor
	//stores inside the modules array all the modules and at the same time initializes them
	int i = 0;
	modules[i++] = window = new Window();
	modules[i++] = render = new Render();
	modules[i++] = input = new Input();
	modules[i++] = textures = new TextureManager();
	modules[i++] = level = new Level();
	modules[i++] = player = new Player();
	
}	

Game::~Game() { //~ symbol means deconstructor
	for (int i = NUM_MODULES-1; i >= 0; i--)
	{
		delete modules[i];
	}
}
bool Game::Init() { //parameters that init takes
	bool ret = true;
	//Disabling the modules that are not necessary at the beggining
	//player->Disable();


	//Init Audio
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
	backgroundSound = Mix_LoadMUS("Assets/facetosol.mp3");

	for (int i = 0; i < NUM_MODULES && ret == true; ++i)
		ret = modules[i]->Init();

	for (int i = 0; i < NUM_MODULES && ret == true; ++i)
		ret = modules[i]->IsEnabled() ? modules[i]->Start() : true;

	Mix_PlayMusic(backgroundSound, -1);
	return ret;
}
update_status Game::Update(){
	
	update_status ret = UPDATE_CONTINUE;
	for (int i = 0; i < NUM_MODULES && ret == UPDATE_CONTINUE; ++i)
		ret = modules[i]->IsEnabled() ? modules[i]->PreUpdate() : UPDATE_CONTINUE;

	for (int i = 0; i < NUM_MODULES && ret == UPDATE_CONTINUE; ++i)
		ret = modules[i]->IsEnabled() ? modules[i]->Update() : UPDATE_CONTINUE;

	for (int i = 0; i < NUM_MODULES && ret == UPDATE_CONTINUE; ++i)
		ret = modules[i]->IsEnabled() ? modules[i]->PostUpdate() : UPDATE_CONTINUE;

	return ret;
}

bool Game::CleanUp()
{
	bool ret = true;

	for (int i = NUM_MODULES - 1; i >= 0 && ret == true; --i)
		ret = modules[i]->IsEnabled() ? modules[i]->CleanUp() : true;
	Mix_CloseAudio();
	Mix_FreeMusic(backgroundSound);
	return ret;
}

