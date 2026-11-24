/*******************************************************************************************
*
*   raylib game template
*
*   <Game title>
*   <Game description>
*
*   This game has been created using raylib (www.raylib.com)
*   raylib is licensed under an unmodified zlib/libpng license (View raylib.h for details)
*
*   Copyright (c) 2021 Ramon Santamaria (@raysan5)
*
********************************************************************************************/
#pragma once

#include "raylib.h"
#include "Game/GlobalGameDefines.h"
#include "Game/Managers/GameManager.h"
#include "Game/Managers/AudioManager.h"

//----------------------------------------------------------------------------------
// Main entry point
//----------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //---------------------------------------------------------
    InitWindow(GameGlobalVar::screenWidth, GameGlobalVar::screenHeight, "FROGGER SIMULATOR");

    AudioManager::Get().Init();

    GameManager & GameMngr = GameManager::GetGameManager();
    GameMngr.InitGame();
    
        SetTargetFPS(60);       // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {

        float deltaTime = GetFrameTime();

        AudioManager::Get().Update();

        //Update Frame
        GameMngr.UpdateFrame(deltaTime);
        
        //Draw Frame
        GameMngr.GetGameManager().DrawFrame();
    }

    // De-Initialization
    GameManager::GetGameManager().UnloadGame();
    AudioManager::Get().Unload();

    CloseWindow();          // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
