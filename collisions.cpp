#include <iostream>
#include "collisions.hpp"
#include <string>

CollisionsDetection::CollisionsDetection()
{
}

bool CollisionsDetection::collisionsPlayerWall(sf::Vector2f &playerPos, int (levelXMap)[400], unsigned int width, unsigned int height, std::string direction)
{
    for (int x = 0; x < width; x++)
    {
      for (int y = 0; y < height; y++)
      {
        if (levelXMap[x + y * width])
        {
            if (direction == "left")
            {
                if (playerPos.x < (x * 64 + 64 -1)
                    && playerPos.x > (x * 64) + 64 -16
                    && playerPos.y < (y * 64 + 32 -1)
                    && playerPos.y > y * 64 - 32)
                {
                    return true;
                }
            }
            if (direction == "right")
            {
                if (playerPos.x > (x * 64 - 32)
                    && playerPos.x < (x * 64 -32) + 16
                    && playerPos.y < (y * 64 + 32 -1)
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
                if (playerPos.y > (y * 64 - 32 - 16)
                    && playerPos.y < (y * 64)
                    && playerPos.x < (x * 64 + 32 -1)
                    && playerPos.x > x * 64 -32)
                {
                    return true;
                }
            }
        }
      }
    }
}
