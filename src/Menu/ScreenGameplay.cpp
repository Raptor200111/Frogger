
#pragma once

#include "ScreenGameplay.h"
#include "Game/Managers/AudioManager.h"



ScreenGameplayState::ScreenGameplayState()
{
	
}

ScreenGameplayState& ScreenGameplayState::getInstance()
{
	static ScreenGameplayState singleton;
	return singleton;
}

void ScreenGameplayState::InitScreen(void)
{
	framesCounter = 0;
	finishScreen = 0;
	timeRemaining = maxTime;
	wallStateCounter = 0;
	for (int i = 0; i < GameGlobalVar::COLS; i++)
	{
		wallState[i] = (i % 2 == 0) ? 0 : 1;
	}

	GameManager& GameInst = GameManager::GetGameManager();
	GameInst.ResetLifes();
	GameInst.SetScore(0);
	GameInst.ResetGameOutcome();
	
	player = new Player();
	player->InitSprite();

	lanes = new Lane[GameGlobalVar::lanesCount];
	for (int i = 0; i < GameGlobalVar::lanesCount; i++)
	{
		lanes[i].Init(GameGlobalVar::Y_POS_LANES[i], GameGlobalVar::texture_LANES[i], GameGlobalVar::textureWidth_LANES[i], GameGlobalVar::speed_LANES[i], GameGlobalVar::direction_LANES[i], GameGlobalVar::maxEntities_LANES[i], GameGlobalVar::entityType_LANES[i]);
	}
	floor = new Sprite();
	floor->InitSprite( {"resources/Game/Floor.png"} );
	wall = new Sprite();
	wall->InitSprite( { "resources/Game/Bush.png", "resources/Game/Home.png", "resources/Game/Point.png" } );
	life = new Sprite();
	life->InitSprite({ "resources/Game/Life.png" });

	AudioManager::Get().StopMenuMusic();
	AudioManager::Get().LoadGameplaySfx();

	showDebugGrid = false;
}

void ScreenGameplayState::UpdateScreen(float deltaTime)
{
	EvaluateInput();

	for (int i = 0; i < GameGlobalVar::lanesCount; i++)
	{
		lanes[i].Update(deltaTime);
	}

	if (player->IsOnLog())
	{
		player->ApplyCarry(deltaTime);
		if (player->IsOutsidePlayfield())
		{
			LoseLife();
			return;
		}
	}

	player->Update(deltaTime);
	timeRemaining -= deltaTime;
	if (timeRemaining <= 0.0f)
	{
		LoseLife();
		return;
	}
	CheckCollisions();
}

void ScreenGameplayState::DrawScreen(void)
{
	DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), BLACK);

	GameManager& GameInst = GameManager::GetGameManager();

	DrawText("SCORE:", 300.f, 10.f, 25, WHITE);
	DrawText(to_string(GameInst.GetScore()).c_str(), 440.f, 10.f, 25, WHITE);

	for (int i = 0; i < GameGlobalVar::COLS; i++)
	{
		floor->position = { (float)GameGlobalVar::screenOffsetX + i * GameGlobalVar::CELL_SIZE, (float)(GameGlobalVar::screenOffsetY + 6 * GameGlobalVar::CELL_SIZE) };
		floor->Draw();
	}
	for (int i = 0; i < GameGlobalVar::COLS; i++)
	{
		floor->position = { (float)GameGlobalVar::screenOffsetX + i * GameGlobalVar::CELL_SIZE, (float)(GameGlobalVar::screenOffsetY + 12 * GameGlobalVar::CELL_SIZE) };
		floor->Draw();
	}
	for (int i = 0; i < GameGlobalVar::COLS; i++)
	{
		wall->SetTextureIndex(wallState[i]);
		wall->position = { (float)GameGlobalVar::screenOffsetX + i * GameGlobalVar::CELL_SIZE, (float)(GameGlobalVar::screenOffsetY) };
		wall->Draw();
	}
	for (int i = 0; i < GameGlobalVar::lanesCount; i++)
	{
		lanes[i].Draw();
	}
	player->Draw();

	if (showDebugGrid)
		DrawDebug();

	const int uiMargin = 10;
	const int timeBarWidth = 250;
	const int timeBarHeight = 20;
	const int timeBarY = GetScreenHeight() - uiMargin - timeBarHeight;
	float timeRatio = timeRemaining / maxTime;
	if (timeRatio < 0.0f)
		timeRatio = 0.0f;

	DrawRectangle(uiMargin, timeBarY, timeBarWidth, timeBarHeight, DARKGRAY);
	DrawRectangle(uiMargin, timeBarY, (int)(timeBarWidth * timeRatio), timeBarHeight, YELLOW);

	for (int i = 0; i < GameInst.GetLifes(); i++)
	{
		life->position = {
			(float)(GetScreenWidth() - uiMargin - GameGlobalVar::CELL_SIZE - i * (GameGlobalVar::CELL_SIZE + uiMargin)),
			(float)(GetScreenHeight() - uiMargin - GameGlobalVar::CELL_SIZE)
		};
		life->Draw();
	}
}

void ScreenGameplayState::UnloadScreen(void)
{
	AudioManager::Get().UnloadGameplaySfx();

	delete player;
	player = nullptr;

	delete[] lanes;
	lanes = nullptr;

	delete floor;
	floor = nullptr;

	delete wall;
	wall = nullptr;

	delete life;
	life = nullptr;
}

int  ScreenGameplayState::FinishScreen(void)
{
	return finishScreen;
}

void ScreenGameplayState::EvaluateInput()
{
	if (IsKeyPressed(KEY_F1))
		showDebugGrid = !showDebugGrid;

	if (IsKeyPressed(KEY_ENTER) || IsGestureDetected(GESTURE_TAP))
	{
		GameManager::GetGameManager().EndGame(false);
		finishScreen = 4;   // END SCREEN
	}
}

void ScreenGameplayState::DebugOptions()
{
}

void ScreenGameplayState::DrawDebug()
{
	bool alternateColor = false;
	for (int row = 0; row < GameGlobalVar::ROWS; row++)
	{
		alternateColor = (row % 2 != 0);
		for (int col = 0; col < GameGlobalVar::COLS; col++)
		{
			const int x = GameGlobalVar::screenOffsetX + col * GameGlobalVar::CELL_SIZE;
			const int y = GameGlobalVar::screenOffsetY + row * GameGlobalVar::CELL_SIZE;
			Color cellColor = alternateColor ? Fade(RED, 0.35f) : Fade(BLUE, 0.35f);
			DrawRectangle(x, y, GameGlobalVar::CELL_SIZE, GameGlobalVar::CELL_SIZE, cellColor);

			const float cx = x + GameGlobalVar::CELL_SIZE * 0.5f;
			const float cy = y + GameGlobalVar::CELL_SIZE * 0.5f;
			DrawCircleV({ cx, cy }, 3.5f, YELLOW);

			alternateColor = !alternateColor;
		}
	}
}

void ScreenGameplayState::ResetTime()
{
	timeRemaining = maxTime;
}

void ScreenGameplayState::LoseLife()
{
	AudioManager::Get().PlaySquash();
	GameManager& GameInst = GameManager::GetGameManager();
	GameInst.DecreaseLife();
	ResetTime();
	player->ResetPlayerPosition();

	if (GameInst.GetLifes() == 0)
	{
		GameInst.EndGame(false);
		finishScreen = 4;
	}
}

int ScreenGameplayState::GetLaneIndexForRow(int row) const
{
	if (row >= 1 && row <= 5)
		return row - 1;
	if (row >= 7 && row <= 11)
		return row - 2;
	return -1;
}

void ScreenGameplayState::CheckCollisions()
{
	auto gridPosition = player->gridPosition;
	if (gridPosition.y == 0)
	{
		player->ClearLogCarry();
		int col = (int)gridPosition.x;
		if (col < 0 || col >= GameGlobalVar::COLS)
		{
			LoseLife();
			return;
		}
		if (wallState[col] == 0 || wallState[col] == 2)
		{
			player->ResetLastGridPosition();
		}
		else if (wallState[col] == 1)
		{
			wallState[col] = 2; // Mark as reached
			AudioManager::Get().PlayPlunk();
			player->ResetPlayerPosition();
			GameManager::GetGameManager().IncreaseScore(100);
			ResetTime();
			if (++wallStateCounter == 7)
			{
				GameManager::GetGameManager().EndGame(true);
				finishScreen = 4;
			}
		}
		return;
	}

	const int laneIndex = GetLaneIndexForRow((int)gridPosition.y);
	if (laneIndex < 0)
	{
		player->ClearLogCarry();
		return;
	}

	Lane& lane = lanes[laneIndex];
	const auto activeEntitiesX = lane.GetActiveEntitiesXPositions();
	const int entityWidth = lane.GetEntityWidth();
	const int entityType = lane.GetEntityType();
	const float playerLeft = player->position.x;
	const float playerRight = playerLeft + GameGlobalVar::CELL_SIZE;

	bool overlappingLog = false;
	float hitLogX = 0.0f;

	for (int entityX : activeEntitiesX)
	{
		const bool overlaps = playerLeft < entityX + entityWidth && playerRight > entityX;
		if (!overlaps)
			continue;

		if (entityType == 0)
		{
			LoseLife();
			return;
		}

		if (entityType == 1)
		{
			overlappingLog = true;
			hitLogX = (float)entityX;
			break;
		}
	}

	if (entityType == 1 && overlappingLog)
	{
		player->SetActiveLane(&lane);
		if (!player->IsOnLog())
			player->MountLog(hitLogX, entityWidth, lane.GetSpeed(), lane.GetDirection());
		else
			player->SetLogCarry(lane.GetSpeed(), lane.GetDirection());
	}
	else if (entityType == 1)
	{
		player->ClearLogCarry();
	}
}