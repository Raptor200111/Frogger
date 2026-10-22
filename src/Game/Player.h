#pragma once
#include "Sprite.h"
#include "Lane.h"

class Player : public Sprite
{
public:
	Player();
	void Update(float deltaTime) override;
	void InitSprite();
	Vector2 GetLastGridPosition() { return lastGridPosition; }
	Vector2 gridPosition;
	void ResetLastGridPosition();
	void ResetPlayerPosition();

	bool IsOnLog() const { return onLog; }
	void SetLogCarry(float speed, int direction);
	void ClearLogCarry();
	void ApplyCarry(float deltaTime);
	bool IsOutsidePlayfield() const;
	void SnapToNearestGridColumn();
	bool TryMoveOnLog(int dxCells, Lane& lane);
	void MountLog(float logX, int entityWidth, float speed, int direction);
	void SetActiveLane(Lane* lane) { activeLane = lane; }

private:
	void HandleInput();
	void SetGridPosition(int column, int row);
	bool IsPositionValid(Vector2 position);
	bool IsPlayerFullyOnLog(float playerX, float logX, int entityWidth) const;

	Vector2 lastGridPosition;
	bool onLog = false;
	float logSpeed = 0.0f;
	int logDirection = 0;
	Lane* activeLane = nullptr;
};
