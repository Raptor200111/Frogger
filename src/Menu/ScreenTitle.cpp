#include "ScreenTitle.h"
#include "raylib.h"
#include "Game/Managers/GameManager.h"

ScreenTitleState& ScreenTitleState::getInstance()
{
	static ScreenTitleState singleton;
	return singleton;
}


void ScreenTitleState::InitScreen(void)
{
	framesCounter = 0;
	finishScreen = 0;
	TraceLog(LOG_INFO, "ScreenTitleState::InitScreen");

	titleLogo = LoadTexture("resources/Menu/MainLogo.png");
	logoLoaded = true;

	entranceDone = false;
	animOffsetY = -(float)(kLogoFinalY + titleLogo.height);
	blinkTimer = 0.0f;
	pressVisible = true;
}

void ScreenTitleState::UpdateScreen(float deltaTime)
{
	if (!entranceDone)
	{
		const float startOffset = -(float)(kLogoFinalY + titleLogo.height);
		const float dropSpeed = -startOffset / kDropDuration; // positive: moves toward 0

		animOffsetY += dropSpeed * deltaTime;
		if (animOffsetY >= 0.0f)
		{
			animOffsetY = 0.0f;
			entranceDone = true;
			blinkTimer = 0.0f;
			pressVisible = true;
		}
		return;
	}

	blinkTimer += deltaTime;
	const float phaseDuration = pressVisible ? kBlinkOn : kBlinkOff;
	if (blinkTimer >= phaseDuration)
	{
		blinkTimer -= phaseDuration;
		pressVisible = !pressVisible;
	}

	if (IsKeyPressed(KEY_ENTER) || IsGestureDetected(GESTURE_TAP))
	{
		finishScreen = 2;   // GAMEPLAY
	}

	if (IsKeyPressed(KEY_O))
	{
		finishScreen = 1;   // OPTIONS
	}
}

void ScreenTitleState::DrawScreen(void)
{
	DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), BLACK);

	const int offsetY = (int)animOffsetY;

	if (logoLoaded)
	{
		int x = (GetScreenWidth() / 2) - (titleLogo.width / 2);
		DrawTexture(titleLogo, x, kLogoFinalY + offsetY, WHITE);
	}

	const char* author = "by Alvar Dalda";
	DrawText(author, (GetScreenWidth() / 2) - (MeasureText(author, 20) / 2), kAuthorFinalY + offsetY, 20, WHITE);

	const char* pressEnter = "PRESS ENTER TO PLAY";
	if (!entranceDone || pressVisible)
	{
		DrawText(pressEnter, (GetScreenWidth() / 2) - (MeasureText(pressEnter, 25) / 2), kPressFinalY + offsetY, 25, WHITE);
	}

	const char* options = "Press 'O' for Instructions";
	DrawText(options, (GetScreenWidth() / 2) - (MeasureText(options, 25) / 2), kOptionsFinalY + offsetY, 25, WHITE);
}

void ScreenTitleState::UnloadScreen(void)
{
	if (logoLoaded) { UnloadTexture(titleLogo); logoLoaded = false; }
}

int ScreenTitleState::FinishScreen(void)
{
	return finishScreen;
}
