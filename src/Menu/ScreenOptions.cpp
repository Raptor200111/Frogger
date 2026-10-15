#include "ScreenOptions.h"
#include "raylib.h"


ScreenOptionsState::ScreenOptionsState()
{

}

ScreenOptionsState& ScreenOptionsState::getInstance()
{
	static ScreenOptionsState singleton;
	return singleton;
}

void ScreenOptionsState::InitScreen(void)
{
	framesCounter = 0;
	finishScreen = 0;
}

void ScreenOptionsState::UpdateScreen(float deltaTime)
{
	if (IsKeyPressed(KEY_O))
	{
		finishScreen = 1;   // TITLE
	}
}

void ScreenOptionsState::DrawScreen(void)
{
    DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), BLACK);

    const char* line1 = "To move FROGGER use the direction keys or W,A,S,D.";
    const char* line2 = "Cross the road by dodging fast-moving cars and trucks.";
    const char* line3 = "Avoid water and predators BY diving turtles and logs.";
    const char* line4 = "Reach and empty home bay at the top before your timer runs out.";
    const char* line5 = "Fill all five bays to complete the level and advance.";
    

    DrawText(line1, (GetScreenWidth() / 2) - (MeasureText(line1, 20) / 2.), 150, 20, WHITE);
    DrawText(line2, (GetScreenWidth() / 2) - (MeasureText(line2, 20) / 2.), 180, 20, WHITE);
    DrawText(line3, (GetScreenWidth() / 2) - (MeasureText(line3, 20) / 2.), 210, 20, WHITE);
    DrawText(line4, (GetScreenWidth() / 2) - (MeasureText(line4, 20) / 2.), 240, 20, WHITE);
    DrawText(line5, (GetScreenWidth() / 2) - (MeasureText(line5, 20) / 2.), 270, 20, WHITE);

    const char* line7 = "Press 'O' to return to Title.";

    DrawText(line7, (GetScreenWidth() / 2.f) - (MeasureText(line7, 20) / 2.), 380, 20, WHITE);

}

void ScreenOptionsState::UnloadScreen(void)
{

}

int ScreenOptionsState::FinishScreen(void)
{
	return finishScreen;
}