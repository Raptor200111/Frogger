#include "Player.h"

Player::Player()
{
	gridPosition = { 7, 12 };
	SetGridPosition(7, 12);
	loaded = false;
	currentTextureIndex = 0;
	onLog = false;
	logSpeed = 0.0f;
	logDirection = 0;
	activeLane = nullptr;
}

void Player::Update(float deltaTime)
{
	HandleInput();
}

void Player::InitSprite()
{
	Sprite::InitSprite({ "resources/Game/Player_D.png", "resources/Game/Player_F.png", "resources/Game/Player_L.png", "resources/Game/Player_R.png" });//Down=0, Front=1, Left=2, Right=3
}

void Player::ResetLastGridPosition()
{
	ClearLogCarry();
	gridPosition = lastGridPosition;
	SetGridPosition((int)gridPosition.x, (int)gridPosition.y);
}

void Player::ResetPlayerPosition()
{
	ClearLogCarry();
	SetGridPosition(7, 12);
}

void Player::SetLogCarry(float speed, int direction)
{
	onLog = true;
	logSpeed = speed;
	logDirection = direction;
}

void Player::ClearLogCarry()
{
	onLog = false;
	logSpeed = 0.0f;
	logDirection = 0;
	activeLane = nullptr;
}

void Player::ApplyCarry(float deltaTime)
{
	if (!onLog)
		return;

	position.x += logSpeed * logDirection * deltaTime;
	gridPosition.x = (position.x - GameGlobalVar::screenOffsetX) / GameGlobalVar::CELL_SIZE;
}

bool Player::IsOutsidePlayfield() const
{
	const float playLeft = (float)GameGlobalVar::screenOffsetX;
	const float playRight = (float)(GameGlobalVar::screenOffsetX + GameGlobalVar::COLS * GameGlobalVar::CELL_SIZE);
	return position.x < playLeft || position.x + GameGlobalVar::CELL_SIZE > playRight;
}

void Player::SnapToNearestGridColumn()
{
	float localX = position.x - GameGlobalVar::screenOffsetX;
	int column = (int)(localX / GameGlobalVar::CELL_SIZE);
	float remainder = localX - column * GameGlobalVar::CELL_SIZE;
	if (remainder >= 25.0f)
		column++;

	if (column < 0)
		column = 0;
	if (column >= GameGlobalVar::COLS)
		column = GameGlobalVar::COLS - 1;

	SetGridPosition(column, (int)gridPosition.y);
}

bool Player::IsPlayerFullyOnLog(float playerX, float logX, int entityWidth) const
{
	return playerX >= logX && (playerX + GameGlobalVar::CELL_SIZE) <= (logX + entityWidth);
}

void Player::MountLog(float logX, int entityWidth, float speed, int direction)
{
	const int slotCount = entityWidth / GameGlobalVar::CELL_SIZE;
	float relative = position.x - logX;
	int slot = (int)(relative / GameGlobalVar::CELL_SIZE);
	float rem = relative - slot * GameGlobalVar::CELL_SIZE;
	if (rem >= 25.0f)
		slot++;

	if (slot < 0)
		slot = 0;
	if (slot >= slotCount)
		slot = slotCount - 1;

	position.x = logX + slot * GameGlobalVar::CELL_SIZE;
	position.y = GameGlobalVar::screenOffsetY + GameGlobalVar::CELL_SIZE * gridPosition.y;
	gridPosition.x = (position.x - GameGlobalVar::screenOffsetX) / GameGlobalVar::CELL_SIZE;
	SetLogCarry(speed, direction);
}

bool Player::TryMoveOnLog(int dxCells, Lane& lane)
{
	const float newX = position.x + dxCells * GameGlobalVar::CELL_SIZE;
	const int entityWidth = lane.GetEntityWidth();
	const auto entitiesX = lane.GetActiveEntitiesXPositions();

	for (int logX : entitiesX)
	{
		if (IsPlayerFullyOnLog(newX, (float)logX, entityWidth))
		{
			lastGridPosition = gridPosition;
			position.x = newX;
			gridPosition.x = (position.x - GameGlobalVar::screenOffsetX) / GameGlobalVar::CELL_SIZE;
			return true;
		}
	}

	float localX = newX - GameGlobalVar::screenOffsetX;
	int column = (int)(localX / GameGlobalVar::CELL_SIZE);
	float remainder = localX - column * GameGlobalVar::CELL_SIZE;
	if (remainder >= 25.0f)
		column++;

	if (column < 0 || column >= GameGlobalVar::COLS)
		return false;

	ClearLogCarry();
	SetGridPosition(column, (int)gridPosition.y);
	return true;
}

void Player::HandleInput()
{
	if (IsKeyPressed(KEY_W) || IsKeyPressed(KEY_UP))
	{
		if (onLog)
		{
			SnapToNearestGridColumn();
			ClearLogCarry();
		}
		if (IsPositionValid({ gridPosition.x, gridPosition.y - 1 }))
		{
			SetGridPosition((int)gridPosition.x, (int)gridPosition.y - 1);
			currentTextureIndex = 1; // Up texture
		}
	}
	else if (IsKeyPressed(KEY_S) || IsKeyPressed(KEY_DOWN))
	{
		if (onLog)
		{
			SnapToNearestGridColumn();
			ClearLogCarry();
		}
		if (IsPositionValid({ gridPosition.x, gridPosition.y + 1 }))
		{
			SetGridPosition((int)gridPosition.x, (int)gridPosition.y + 1);
			currentTextureIndex = 0; // Down texture
		}
	}
	else if (IsKeyPressed(KEY_A) || IsKeyPressed(KEY_LEFT))
	{
		if (onLog && activeLane != nullptr)
		{
			if (TryMoveOnLog(-1, *activeLane))
				currentTextureIndex = 2;
		}
		else if (IsPositionValid({ gridPosition.x - 1, gridPosition.y }))
		{
			SetGridPosition((int)gridPosition.x - 1, (int)gridPosition.y);
			currentTextureIndex = 2; // Left texture
		}
	}
	else if (IsKeyPressed(KEY_D) || IsKeyPressed(KEY_RIGHT))
	{
		if (onLog && activeLane != nullptr)
		{
			if (TryMoveOnLog(1, *activeLane))
				currentTextureIndex = 3;
		}
		else if (IsPositionValid({ gridPosition.x + 1, gridPosition.y }))
		{
			SetGridPosition((int)gridPosition.x + 1, (int)gridPosition.y);
			currentTextureIndex = 3; // Right texture
		}
	}
}

void Player::SetGridPosition(int column, int row)
{
	lastGridPosition = gridPosition;
	gridPosition = { float(column), float(row) };
	position = { GameGlobalVar::screenOffsetX + (GameGlobalVar::CELL_SIZE * gridPosition.x), GameGlobalVar::screenOffsetY + (GameGlobalVar::CELL_SIZE * gridPosition.y) };
}

bool Player::IsPositionValid(Vector2 position) {
	return position.x >= 0 && position.x < GameGlobalVar::COLS && position.y >= 0 && position.y < GameGlobalVar::ROWS;
}
