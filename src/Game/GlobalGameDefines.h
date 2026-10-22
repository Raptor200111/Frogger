#pragma once
//----------------------------------------------------------------------------------
// Local Variables Definition (local to this module)
//----------------------------------------------------------------------------------
#ifndef GLOBALVARIABLES_H
#define GLOBALVARIABLES_H

#include <string>

namespace GameGlobalVar
{
	const int screenWidth = 800;
	const int screenHeight = 800;

	const int gravity = 400;

	const int CELL_SIZE = 48;
	const int ROWS = 13;
	const int COLS = 14;

	const int screenOffsetX = (screenWidth - (CELL_SIZE * COLS)) / 2;
	const int screenOffsetY = (screenHeight - (CELL_SIZE * ROWS)) / 2;

	const int lanesCount = 10; //lanes go top to bottom 0 to 4 (1 to 5 on the grid), 5 to 9 (7 to 11 on the grid)
	const int Y_POS_LANES[10] = { 1*CELL_SIZE + screenOffsetY, 2*CELL_SIZE + screenOffsetY, 3*CELL_SIZE + screenOffsetY, 4*CELL_SIZE + screenOffsetY, 5*CELL_SIZE + screenOffsetY, 7*CELL_SIZE + screenOffsetY, 8*CELL_SIZE + screenOffsetY, 9*CELL_SIZE + screenOffsetY, 10*CELL_SIZE + screenOffsetY, 11*CELL_SIZE + screenOffsetY };
	const std::string texture_LANES[10] = { "resources/Game/Enemies/Log2U.png", "resources/Game/Enemies/TurtleEnabled.png", "resources/Game/Enemies/Log4U.png", "resources/Game/Enemies/Log1U.png", "resources/Game/Enemies/TurtleEnabled.png", "resources/Game/Enemies/Truck5.png", "resources/Game/Enemies/Truck4.png", "resources/Game/Enemies/Truck3.png", "resources/Game/Enemies/Truck2.png", "resources/Game/Enemies/Truck1.png" };
	const int textureWidth_LANES[10] = { 192, 48, 288, 144, 48, 96, 48, 48, 48, 48 };
	const float speed_LANES[10] = { 100.0f, 130.0f, 100.0f, 100.0f, 130.0f, 140.0f, 130.0f, 120.0f, 110.0f, 100.0f };
	const int direction_LANES[10] = { 1, -1, 1, 1, -1, -1, 1, -1, -1, -1 };
	const int maxEntities_LANES[10] = { 3, 3, 3, 3, 3, 3, 3, 3, 3, 3 };
	const int entityType_LANES[10] = { 1, 0, 1, 1, 0, 0, 0, 0, 0, 0 };
}

#endif