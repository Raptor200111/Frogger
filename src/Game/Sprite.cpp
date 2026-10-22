#include "Sprite.h"

Sprite::Sprite()
{
	position = { 0.0f, 0.0f };
	loaded = false;
	currentTextureIndex = 0;
}

Sprite::~Sprite()
{
	UnloadSprite();
}

void Sprite::InitSprite(const std::vector<std::string>& texturePath)
{
	texture = vector<Texture2D>(texturePath.size());
	for (size_t i = 0; i < texturePath.size(); ++i)
	{
		texture[i] = LoadTexture(texturePath[i].c_str());
	}
	loaded = true;
}

void Sprite::InitSprite(vector<Texture2D>& textures)
{
	texture = textures;
	loaded = true;
}

void Sprite::UnloadSprite()
{
	if (loaded)
	{
		for (size_t i = 0; i < texture.size(); ++i)
		{
			UnloadTexture(texture[i]);
		}
		loaded = false;
	}
}

void Sprite::Update(float deltaTime)
{
	// Update sprite logic here (if needed)
}

void Sprite::Draw()
{
	if (loaded)
	{
		DrawTextureV(texture[currentTextureIndex], position, WHITE);
	}
}
