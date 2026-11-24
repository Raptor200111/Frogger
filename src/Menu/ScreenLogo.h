#pragma once
#include "StateMachineMngr.h"
#include "raylib.h"

class ScreenLogoState : public StateMachineMngr
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

	int getScreenId() { return (int)ScreenState::LOGO; }

	static ScreenLogoState& getInstance();

private:
	ScreenLogoState();
	ScreenLogoState(const ScreenLogoState& other);
	ScreenLogoState& operator= (const ScreenLogoState& other);

	int finishScreen = 0;
	int state = 0; // 0 fade in, 1 hold, 2 fade out
	float alpha = 0.0f;
	float stateTimer = 0.0f;

	Texture2D logoTexture = { 0 };
	bool logoLoaded = false;

	static constexpr float kFadeInDuration = 0.6f;
	static constexpr float kHoldDuration = 2.0f;
	static constexpr float kFadeOutDuration = 0.6f;
};
