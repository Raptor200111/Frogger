#pragma once
#include "StateMachineMngr.h"
#include "../Game/Player.h"
#include "../Game/Lane.h"
#include "raylib.h"
#include "Game/GlobalGameDefines.h"
#include <string>
#include "../Game/Managers/GameManager.h"


class ScreenGameplayState : public StateMachineMngr
{
public:

	void enter(Screen* screen) {}
	void toggle(Screen* screen) {};
	void exit(Screen* screen) {};

	virtual void InitScreen(void);
	virtual void UpdateScreen(float deltaTime);
	virtual void DrawScreen(void);
	virtual void UnloadScreen(void);
	virtual int FinishScreen(void);

	int getScreenId() { return (int)ScreenState::GAMEPLAY; }

	static ScreenGameplayState& getInstance();

private:
	ScreenGameplayState();
	ScreenGameplayState(const ScreenGameplayState& other);
	ScreenGameplayState& operator= (const ScreenGameplayState& other);

	void EvaluateInput();
	
	void DebugOptions();
	void DrawDebug();
	void ResetTime();
	void LoseLife();

	int framesCounter = 0;
	int finishScreen = 0;
	bool mb_ReplayLevel = false;

	bool debug_floor = false;
	bool debug_stairs = false;

	Player* player = nullptr;
	Lane* lanes = nullptr;
	Sprite* floor = nullptr;
	Sprite* wall = nullptr;
	Sprite* life = nullptr;

	const float maxTime = 20.0f;
	float timeRemaining = maxTime;

	int wallState[GameGlobalVar::COLS] = { 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1 };
	int wallStateCounter = 0;

	void CheckCollisions();
	int GetLaneIndexForRow(int row) const;
};