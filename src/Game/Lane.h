#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "raylib.h"
#include "GlobalGameDefines.h"
#include "Sprite.h"

using namespace std;

class Lane
{
public:
	Lane();
	~Lane();

	void Init(int y,string tex, int texWidth, float spe, int dir,	int maxEnt, int entType);
	void Unload();
	void Update(float deltaTime);
	void Draw();
	int GetEntityWidth() { return textureWidth; }
	vector<int> GetActiveEntitiesXPositions() {
		vector<int> positions;
		for (int i = 0; i < maxEntities; i++)
		{
			if (active[i])
			{
				positions.push_back((int)entityPositions[i].x);
			}
		}
		return positions;
	}
	int GetEntityType() { return entityType; }

private:
	int yPosition;
	Vector2 textureSize;
	float speed;
	int direction;
	int maxEntities;
	int entityType;
	int textureWidth;

	Sprite* entity = nullptr;
	Vector2* entityPositions = nullptr;
	int available;
	bool* active = nullptr;
	int indexUse = 0;
	bool loaded = false;

	float spawnTimer = 0.0f;
	int minSpawnSpace = 1.0f;
	int maxSpawnSpace = 3.0f;
};