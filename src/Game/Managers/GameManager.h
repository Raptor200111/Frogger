#pragma once

#include "raylib.h"

#include "Menu/StateMachineMngr.h" 

using namespace std;


class GameManager
{
private:


public:
	GameManager();

	void InitGame();						// Initialize game
	void UpdateFrame(float deltaTime);      // Update game (one frame)
	void DrawFrame(void);                    // Draw game (one frame)
	void UnloadGame(void);

	void ClearGameVar();

	Font& GetFont() { return font; }

	int GetScore() { return score; }
	void SetScore(int newValue) { score = newValue < minScore ? minScore : (newValue > maxScore ? maxScore : newValue); }

	int GetHighScore() { return highScore; }
	bool HasWon() { return gameWon; }
	void EndGame(bool won);
	void ResetGameOutcome() { gameWon = false; }

	int GetSeconds() { return seconds; }
	void SetSeconds(int newValue) { seconds = newValue; }

	int GetLifes() { return lifes; }
	void DecreaseLife() { if (lifes > 0) { lifes--; DecreaseScore(50); } }
	void ResetLifes() { lifes = 3; }

	void IncreaseScore(int newValue) { SetScore(score + newValue); }
	void DecreaseScore(int newValue) { SetScore(score - newValue); }

	static GameManager& GetGameManager();

private:
	//----------------------------------------------------
	//TODO to move to ScreensMngr?
	void ChangeToScreen(int screen);     // Change to screen, no transition effect

	void TransitionToScreen(int screen); // Request transition to next screen
	void UpdateTransition(void);         // Update transition effect
	void DrawTransition(void);           // Draw transition effect (full-screen rectangle)


	float transAlpha = 0.0f;
	bool onTransition = false;
	bool transFadeOut = false;
	int transFromScreen = -1;
	int transToScreen = -1;

	int lifes = 3;
	int score = 0;
	int highScore = 0;
	int seconds = 0;
	bool gameWon = false;

	static constexpr int minScore = -150;
	static constexpr int maxScore = 700;

	void LoadHighScore();
	void SaveHighScore();

private:

	static GameManager *GameMngr;

	//------------

	Font font = { 0 };
	Music music = { 0 };
	Sound fxCoin = { 0 };

	StateMachineMngr* ScreenState;

};