#include "ScreenLogo.h"
#include "raylib.h"

ScreenLogoState::ScreenLogoState()
{}

ScreenLogoState& ScreenLogoState::getInstance()
{
	static ScreenLogoState singleton;
	return singleton;
}

void ScreenLogoState::InitScreen(void)
{
	finishScreen = 0;
	state = 0;
	alpha = 0.0f;
	stateTimer = 0.0f;

	logoTexture = LoadTexture("resources/Menu/robot.png");
	logoLoaded = true;
}

void ScreenLogoState::UpdateScreen(float deltaTime)
{
	stateTimer += deltaTime;

	if (state == 0)
	{
		alpha = stateTimer / kFadeInDuration;
		if (alpha >= 1.0f)
		{
			alpha = 1.0f;
			state = 1;
			stateTimer = 0.0f;
		}
	}
	else if (state == 1)
	{
		alpha = 1.0f;
		if (stateTimer >= kHoldDuration)
		{
			state = 2;
			stateTimer = 0.0f;
		}
	}
	else if (state == 2)
	{
		alpha = 1.0f - (stateTimer / kFadeOutDuration);
		if (alpha <= 0.0f)
		{
			alpha = 0.0f;
			finishScreen = 1;
		}
	}
}

void ScreenLogoState::DrawScreen(void)
{
	DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), BLACK);

	if (!logoLoaded)
		return;

	const int robotX = (GetScreenWidth() - logoTexture.width) / 2;
	const int robotY = (GetScreenHeight() - logoTexture.height) / 2;

	const char* madeBy = "made by";
	const int madeBySize = 20;
	const int madeByX = (GetScreenWidth() - MeasureText(madeBy, madeBySize)) / 2;
	const int madeByY = robotY - 27;

	DrawText(madeBy, madeByX, madeByY, madeBySize, Fade(PURPLE, alpha));
	DrawTexture(logoTexture, robotX, robotY, Fade(WHITE, alpha));
}

void ScreenLogoState::UnloadScreen(void)
{
	if (logoLoaded)
	{
		UnloadTexture(logoTexture);
		logoLoaded = false;
	}
}

int ScreenLogoState::FinishScreen(void)
{
	return finishScreen;
}
