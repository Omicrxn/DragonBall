#pragma once
#ifndef __Audio_H__
#define __Audio_H__

#include "Globals.h"
#include "Module.h"
#include "SDL_mixer.h"

#define FADE_TIME 2.0f
#define MAX_FX 200

class Audio : public Module
{
public:

	Audio();
	~Audio();

	bool Init();
	bool CleanUp();

	// Play a music file
	bool PlayMusic(const char* path, float fade_time = FADE_TIME);
	bool StopMusic();

	// Load a WAV in memory
	uint LoadFx(const char* path);
	bool UnLoadFx(uint id);

	// Play a previously loaded WAV
	bool PlayFx(uint fx, int repeat = 0);

private:

	Mix_Music* music = nullptr;
	Mix_Chunk* fx[MAX_FX];
	uint			last_fx = 1;
};

#endif // __Audio_H__