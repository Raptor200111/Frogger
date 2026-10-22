#pragma once
#include "StateMachineMngr.h"
#include "Screen.h"
#include "raylib.h"

class ScreenTitleState : public StateMachineMngr
{
public:

	void enter(Screen* screen) {}
	void toggle(Screen* screen) {};
	void exit(Screen* screen) {};

	void InitScreen(void);
	void UpdateScreen(float deltaTime);
	void DrawScreen(void);
	void UnloadScreen(void);
	int FinishScreen(void);

	int getScreenId() { return (int)ScreenState::TITLE; }
	static ScreenTitleState& getInstance();

private:

	ScreenTitleState() {};
	ScreenTitleState(const ScreenTitleState& other);
	ScreenTitleState& operator= (const ScreenTitleState& other);

	int framesCounter = 0;
	int finishScreen = 0;

	Texture2D titleLogo = { 0 };
	bool logoLoaded = false;

	bool entranceDone = false;
	float animOffsetY = 0.0f;
	float blinkTimer = 0.0f;
	bool pressVisible = true;

	static constexpr float kDropDuration = 0.45f;
	static constexpr float kBlinkOn = 0.75f;
	static constexpr float kBlinkOff = 0.25f;

	static constexpr int kLogoFinalY = 162;
	static constexpr int kAuthorFinalY = 507;
	static constexpr int kPressFinalY = 557;
	static constexpr int kOptionsFinalY = 612;
};
