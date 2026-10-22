#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "raylib.h"
#include "GlobalGameDefines.h"
using namespace std;

class Sprite
{
public:
    Sprite();
    virtual ~Sprite();

	virtual void InitSprite(const std::vector<std::string>& texturePath);
	virtual void InitSprite(vector<Texture2D>& textures);

	virtual void UnloadSprite();
    virtual void Update(float deltaTime);
    virtual void Draw();
	void SetTextureIndex(int index) { currentTextureIndex = index; }

	Vector2 position;

protected:
	vector<Texture2D> texture;
	
	bool loaded;
	int currentTextureIndex;
};