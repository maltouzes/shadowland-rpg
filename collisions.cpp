#include <iostream>
#include "collisions.hpp"
#include <string>

CollisionsDetection::CollisionsDetection()
{
}

bool CollisionsDetection::collisionsPlayerWall(sf::Vector2f &playerPos, int (levelXMap)[400], unsigned int width, unsigned int height, std::string direction)
{
    int left_tile = playerPos.x / 64;
    int right_tile = (playerPos.x + 64) / 64 + 1;
    int top_tile = playerPos.y / 64;
    int bottom_tile = (playerPos.y + 64) / 64 + 1;
    if (right_tile == 0) right_tile = 1;
    if (bottom_tile == 0) bottom_tile = 1;

    for (int x = left_tile; x < right_tile+1; x++)
    {
      for (int y = top_tile; y < bottom_tile+1; y++)
      {
        if (levelXMap[x + y * width])
        {
            if (direction == "left")
            {
                if (playerPos.x < (x * 64 + 64)
                    && playerPos.x > (x * 64) + 64 -16
                    && playerPos.y < (y * 64 + 32)
                    && playerPos.y > y * 64 - 32)
                {
                    return true;
                }
            }
            if (direction == "right")
            {
                if (playerPos.x + 32 + 16 > (x * 64)
                    && playerPos.x + 32 + 16 < x * 64 + 64 + 16
                    && playerPos.y < (y * 64 + 32)
                    && playerPos.y > y * 64 - 32)
                {
                    return true;
                }
            }
            if (direction == "up")
            {
                if (playerPos.y > (y * 64)
                    && playerPos.y < (y * 64 - 16) + 64
                    && playerPos.x < (x * 64 + 32 + 16)
                    && playerPos.x > x * 64 - 32)
                {
                    return true;
                }
            }
            if (direction == "down")
            {
                if (playerPos.y > (y * 64 - 32 - 20)
                    && playerPos.y < (y * 64)
                    && playerPos.x < (x * 64 + 32)
                    && playerPos.x > x * 64 -32)
                {
                    return true;
                }
            }
        }
      }
    }
}
