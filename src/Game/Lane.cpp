#include "Lane.h"

Lane::Lane()
{}

Lane::~Lane()
{
	Unload();
}

void Lane::Init(int y, string tex, int texWidth, float spe, int dir, int maxEnt, int entType)
{
	speed = spe;
	direction = dir;
	entityType = entType;
	textureWidth = texWidth;

	maxEntities = maxEnt;
	entity = new Sprite();
	entityPositions = new Vector2[maxEnt];
	available = maxEnt;
	active = new bool[maxEnt];
	vector<Texture2D> textures = { LoadTexture(tex.c_str()) };
	entity->InitSprite(textures);
	for (int i = 0; i < maxEnt; i++)
	{
		active[i] = false;
		entityPositions[i] = { (float)-textureWidth, (float)y };
	}
	indexUse = 0;

	minSpawnSpace = textureWidth / GameGlobalVar::CELL_SIZE;
	maxSpawnSpace = GameGlobalVar::ROWS;

	spawnTimer = (GetRandomValue(minSpawnSpace, maxSpawnSpace) * GameGlobalVar::CELL_SIZE) / speed;

	loaded = true;
}

void Lane::Unload()
{
	delete entity;
	entity = nullptr;

	delete[] entityPositions;
	entityPositions = nullptr;

	delete[] active;
	active = nullptr;
	loaded = false;
}

void Lane::Update(float deltaTime)
{
	if (loaded)
	{
		spawnTimer -= deltaTime;
		if (spawnTimer <= 0.0f && available > 0)
		{
			while (active[indexUse])
			{
				indexUse = (indexUse + 1) % maxEntities;
			}

			active[indexUse] = true;
			available--;

			if (direction > 0)
				entityPositions[indexUse].x = -textureWidth; // left
			else
				entityPositions[indexUse].x = GameGlobalVar::screenWidth; // right
			spawnTimer = (GetRandomValue(minSpawnSpace, maxSpawnSpace) * GameGlobalVar::CELL_SIZE) / speed;
		}

		for (int i = 0; i < maxEntities; i++)
		{
			if (active[i])
			{
				entityPositions[i].x += speed * deltaTime * direction;
				if (direction > 0 && entityPositions[i].x > GameGlobalVar::screenWidth)
				{
					active[i] = false;
					available++;
				}
				else if (direction < 0 && entityPositions[i].x < 0 - textureWidth)
				{
					active[i] = false;
					available++;
		}
	}
		}
		}
}

void Lane::Draw()
{
	if (loaded)
		for (int i = 0; i < maxEntities; i++)
		{
			if (active[i])
			{
				entity->position = entityPositions[i];
				entity->Draw();
			}
		}
}
