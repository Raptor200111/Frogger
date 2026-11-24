#include "AudioManager.h"

AudioManager& AudioManager::Get()
{
	static AudioManager instance;
	return instance;
}

void AudioManager::Init()
{
	if (initialized)
		return;

	InitAudioDevice();
	initialized = true;
}

void AudioManager::Update()
{
	if (!initialized)
		return;

	if (menuMusicLoaded && menuMusicPlaying)
		UpdateMusicStream(menuMusic);

	if (gameOverLoaded)
		UpdateMusicStream(gameOverMusic);
}

void AudioManager::Unload()
{
	if (!initialized)
		return;

	StopMenuMusic();
	StopGameOver();
	UnloadGameplaySfx();
	CloseAudioDevice();
	initialized = false;
}

void AudioManager::PlayMenuMusic()
{
	if (!initialized)
		return;

	StopGameOver();

	if (menuMusicPlaying && menuMusicLoaded && IsMusicStreamPlaying(menuMusic))
		return;

	if (!menuMusicLoaded)
	{
		menuMusic = LoadMusicStream("resources/Sounds/Lily_Islands.mp3");
		menuMusic.looping = true;
		menuMusicLoaded = true;
	}

	if (!IsMusicStreamPlaying(menuMusic))
		PlayMusicStream(menuMusic);

	menuMusicPlaying = true;
}

void AudioManager::StopMenuMusic()
{
	if (!menuMusicLoaded)
		return;

	StopMusicStream(menuMusic);
	UnloadMusicStream(menuMusic);
	menuMusic = { 0 };
	menuMusicLoaded = false;
	menuMusicPlaying = false;
}

void AudioManager::PlayGameOver()
{
	if (!initialized)
		return;

	StopMenuMusic();
	StopGameOver();

	gameOverMusic = LoadMusicStream("resources/Sounds/Game_Over.mp3");
	gameOverMusic.looping = false;
	gameOverLoaded = true;
	PlayMusicStream(gameOverMusic);
}

void AudioManager::StopGameOver()
{
	if (!gameOverLoaded)
		return;

	StopMusicStream(gameOverMusic);
	UnloadMusicStream(gameOverMusic);
	gameOverMusic = { 0 };
	gameOverLoaded = false;
}

void AudioManager::LoadGameplaySfx()
{
	if (gameplaySfxLoaded)
		return;

	hopSfx = LoadSound("resources/Sounds/frogger_hop.wav");
	plunkSfx = LoadSound("resources/Sounds/frogger_plunk.wav");
	squashSfx = LoadSound("resources/Sounds/frogger_squash.wav");
	gameplaySfxLoaded = true;
}

void AudioManager::UnloadGameplaySfx()
{
	if (!gameplaySfxLoaded)
		return;

	UnloadSound(hopSfx);
	UnloadSound(plunkSfx);
	UnloadSound(squashSfx);
	hopSfx = { 0 };
	plunkSfx = { 0 };
	squashSfx = { 0 };
	gameplaySfxLoaded = false;
}

void AudioManager::PlayHop()
{
	if (gameplaySfxLoaded)
		PlaySound(hopSfx);
}

void AudioManager::PlayPlunk()
{
	if (gameplaySfxLoaded)
		PlaySound(plunkSfx);
}

void AudioManager::PlaySquash()
{
	if (gameplaySfxLoaded)
		PlaySound(squashSfx);
}
