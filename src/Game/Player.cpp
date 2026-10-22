#include "Player.h"

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
	gridPosition = lastGridPosition;
	SetGridPosition((int)gridPosition.x, (int)gridPosition.y);
}

void Player::HandleInput()
{
	if ((IsKeyPressed(KEY_W) || IsKeyPressed(KEY_UP)) && IsPositionValid({ gridPosition.x, gridPosition.y - 1 }))
	{

		SetGridPosition(gridPosition.x, gridPosition.y - 1);
		currentTextureIndex = 1; // Up texture
	}
	else if ((IsKeyPressed(KEY_S) || IsKeyPressed(KEY_DOWN)) && IsPositionValid({ gridPosition.x, gridPosition.y + 1 }))
	{
		SetGridPosition(gridPosition.x, gridPosition.y + 1);
		currentTextureIndex = 0; // Down texture
	}
	else if ((IsKeyPressed(KEY_A) || IsKeyPressed(KEY_LEFT)) && IsPositionValid({ gridPosition.x -  1, gridPosition.y}))
	{
		SetGridPosition(gridPosition.x - 1, gridPosition.y);
		currentTextureIndex = 2; // Left texture
	}
	else if ((IsKeyPressed(KEY_D) || IsKeyPressed(KEY_RIGHT)) && IsPositionValid({ gridPosition.x + 1, gridPosition.y}))
	{
		SetGridPosition(gridPosition.x + 1, gridPosition.y);
		currentTextureIndex = 3; // Right texture
	}
}

void Player::SetGridPosition(int column, int row)
{
	lastGridPosition = gridPosition;
	gridPosition = { float(column), float(row) };
	position = { GameGlobalVar::screenOffsetX + (GameGlobalVar::CELL_SIZE * gridPosition.x), GameGlobalVar::screenOffsetY + (GameGlobalVar::CELL_SIZE * gridPosition.y) };
}

Player::Player()
{
	gridPosition = { 7, 12 };
	SetGridPosition(7, 12); // Reset to starting position in grid coordinates
	loaded = false;
	currentTextureIndex = 0;
}

bool Player::IsPositionValid(Vector2 position) {
	return position.x >= 0 && position.x < GameGlobalVar::COLS && position.y >= 0 && position.y < GameGlobalVar::ROWS;
}