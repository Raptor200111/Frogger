#include "ScreenEnding.h"
#include "Game/Managers/GameManager.h"

#include "raylib.h"

#include <string>


ScreenEndingState& ScreenEndingState::getInstance()
{
	static ScreenEndingState singleton;
	return singleton;
}


void ScreenEndingState::InitScreen(void)
{
	framesCounter = 0;
	finishScreen = 0;
}

void ScreenEndingState::UpdateScreen(float deltaTime)
{
	if (IsKeyPressed(KEY_ENTER) )
	{
		finishScreen = 1; // GAMEPLAY

	}
	if (IsKeyPressed(KEY_O))
	{
		finishScreen = 2;   // OPTIONS
	}
}

void ScreenEndingState::DrawScreen(void)
{
	DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), BLACK);
	GameManager& GameInst = GameManager::GetGameManager();

	Font font = GameInst.GetFont();

	const char* result = GameInst.HasWon() ? "WIN" : "GAME OVER";
	const int resultWidth = MeasureText(result, 50);
	DrawText(result, (GetScreenWidth() - resultWidth) / 2.f, (GetScreenHeight() / 2.f) - 150 , 50, GameInst.HasWon() ? GREEN : RED);

	const std::string scoreText = "SCORE: " + std::to_string(GameInst.GetScore());
	const std::string highScoreText = "HIGHSCORE: " + std::to_string(GameInst.GetHighScore());
	DrawText(scoreText.c_str(), (GetScreenWidth() - MeasureText(scoreText.c_str(), 25)) / 2, (GetScreenHeight() / 2) - 50, 25, WHITE);
	DrawText(highScoreText.c_str(), (GetScreenWidth() - MeasureText(highScoreText.c_str(), 25)) / 2, (GetScreenHeight() / 2), 25, WHITE);

	DrawText("Press Enter for Playing", (GetScreenWidth() / 2.f) - (MeasureText("Press Enter for Playing", 25) / 2), (GetScreenHeight() / 2.f) + 50, 25, WHITE);
	DrawText("Press 'O' for Options", (GetScreenWidth() / 2.f) - (MeasureText("Press 'O' for Options", 25) / 2), (GetScreenHeight() / 2.f) + 100, 25, WHITE);

}

void ScreenEndingState::UnloadScreen(void)
{
	//Let's unload all the enemies lines
	GameManager& GameInst = GameManager::GetGameManager();

}

int  ScreenEndingState::FinishScreen(void)
{
	return finishScreen;
}