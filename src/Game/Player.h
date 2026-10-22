#pragma once
#include "Sprite.h"

class Player : public Sprite
{
public :
	Player();
    void Update(float deltaTime) override;
	void InitSprite();
	Vector2 GetLastGridPosition() { return lastGridPosition; }
	Vector2 gridPosition;
	void ResetLastGridPosition();
	void ResetPlayerPosition() { SetGridPosition(7, 12); } // Reset to starting position in grid coordinates

private:
	void HandleInput();
	void SetGridPosition(int column, int row);
	bool IsPositionValid(Vector2 position);
	 // Player's position in grid coordinates
	Vector2 lastGridPosition;
};