#pragma once
#include "raylib.h"

class AudioManager
{
public:
	static AudioManager& Get();

	void Init();
	void Update();
	void Unload();

	void PlayMenuMusic();
	void StopMenuMusic();
	void PlayGameOver();
	void StopGameOver();

	void LoadGameplaySfx();
	void UnloadGameplaySfx();
	void PlayHop();
	void PlayPlunk();
	void PlaySquash();

private:
	AudioManager() = default;
	AudioManager(const AudioManager&) = delete;
	AudioManager& operator=(const AudioManager&) = delete;

	bool initialized = false;

	Music menuMusic = { 0 };
	bool menuMusicLoaded = false;
	bool menuMusicPlaying = false;

	Music gameOverMusic = { 0 };
	bool gameOverLoaded = false;

	Sound hopSfx = { 0 };
	Sound plunkSfx = { 0 };
	Sound squashSfx = { 0 };
	bool gameplaySfxLoaded = false;
};
