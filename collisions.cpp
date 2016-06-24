#include <iostream>
#include "collisions.h"
#include <string>

CollisionsDetection::CollisionsDetection()
{
}

int CollisionsDetection::collisionsPlayerWall(sf::Vector2f &playerPos, int (levelXMap)[400], unsigned int width, unsigned int height, std::string direction, bool catchObj)
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
                    if (catchObj)
                      {
                          // std::cout << "levelXMap: ";
                          // std::cout << levelXMap[x + y * width] << std::endl;
                          return levelXMap[x + y * width];
                      }

                    else return true;
                }
            }
            if (direction == "right")
            {
                if (playerPos.x + 32 + 10 > (x * 64)
                    && playerPos.x + 32 + 16 < x * 64 + 64 + 16
                    && playerPos.y < (y * 64 + 32)
                    && playerPos.y > y * 64 - 32 - 12)
                {
                    if (catchObj)
                      {
                          // std::cout << "levelXMap: ";
                          // std::cout << levelXMap[x + y * width] << std::endl;
                          return levelXMap[x + y * width];
                      }

                    else return true;
                }
            }
            if (direction == "up")
            {
                if (playerPos.y > (y * 64)
                    && playerPos.y < (y * 64 - 16) + 64
                    && playerPos.x < (x * 64 + 32 + 28)
                    && playerPos.x > x * 64 - 32 - 8)
                {
                    if (catchObj)
                    {
                        // std::cout << "levelXMap: ";
                        // std::cout << levelXMap[x + y * width] << std::endl;
                        return levelXMap[x + y * width];
                    }

                    else return true;
                }
            }
            if (direction == "down")
            {
                if (playerPos.y > (y * 64 - 32 - 20)
                    && playerPos.y < (y * 64)
                    && playerPos.x < (x * 64 + 32 + 28)
                    && playerPos.x > x * 64 -32 - 8)
                {
                    if (catchObj)
                      {
                          // std::cout << "levelXMap: ";
                          // std::cout << levelXMap[x + y * width] << std::endl;
                          return levelXMap[x + y * width];
                      }

                    else return true;
                }
            }
        }
      }
    }
    return 0;
}

int CollisionsDetection::playerTakeObj(sf::Vector2f &playerPos, int (levelXMap)[400], unsigned int width, unsigned int height, std::string direction)
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
        if (levelXMap[x + y * width]) return x + y * width;
      }
    }


    return 0;
}

int CollisionsDetection::playerEnemies(sf::Vector2f &playerPos, sf::Vector2f &enemiesPos)
{
    // std::cout << "playerPos y " << playerPos.y << std::endl;
    // std::cout << "enemiesPos y " << enemiesPos.y << std::endl;

    if (enemiesPos.x < playerPos.x + 32 && enemiesPos.x > playerPos.x + 16 && enemiesPos.y < playerPos.y + 50 && playerPos.y < enemiesPos.y + 32)
    {
        std::cout << "player go to left" << std::endl;
        return -96;
    }

    if (enemiesPos.x + 32 > playerPos.x && enemiesPos.x < playerPos.x - 16 && enemiesPos.y < playerPos.y + 50 && playerPos.y < enemiesPos.y + 32)
    {
        std::cout << "player go to right" << std::endl;
        return 96;
    }

    if (enemiesPos.y < playerPos.y + 32 && enemiesPos.y > playerPos.y + 16 && enemiesPos.x < playerPos.x + 50 && playerPos.x < enemiesPos.x + 32)
    {
        std::cout << "player go to top" << std::endl;
        return -32;
    }

    if (enemiesPos.y + 32 > playerPos.y && enemiesPos.y < playerPos.y - 16 && enemiesPos.x < playerPos.x + 50 && playerPos.x < enemiesPos.x + 32)
    {
        std::cout << "player go to bottom" << std::endl;
        return 32;
    }
    return 0;
}

int CollisionsDetection::playerEnemies(sf::Vector2f &movement, Creature &monster1, Creature &player1)
{
  if (player1.animatedSprite.getGlobalBounds().intersects(monster1.animatedSprite.getGlobalBounds()))
  {
      if (monster1.currentAnimation == &monster1.walkingAnimationUp) movement.y -= 400;
      if (monster1.currentAnimation == &monster1.walkingAnimationDown) movement.y += 400;
      if (monster1.currentAnimation == &monster1.walkingAnimationLeft) movement.x -= 400;
      if (monster1.currentAnimation == &monster1.walkingAnimationRight) movement.x += 400;
  }
  return 0;
}

int CollisionsDetection::playerEnemies(sf::Vector2f &movement, sf::FloatRect mFR, sf::FloatRect pFR)
{
    if (mFR.intersects(pFR))
    {
            movement.y -= 1500;
    }
}

void CollisionsDetection::enemiesMove(sf::Vector2f &movementMonster, Creature &monster1, Creature &player1, int (current2Map)[400], int (current3Map)[400])
{
    int * current2MapP = current2Map;
    int * current3MapP = current3Map;
    sf::Vector2f monsterPos = monster1.animatedSprite.getPosition();

    if (player1.animatedSprite.getGlobalBounds().left < monster1.animatedSprite.getGlobalBounds().left)
    {
            if(!CollisionsDetection::collisionsPlayerWall(monsterPos, current2MapP, 20, 20, "left", 0) && !CollisionsDetection::collisionsPlayerWall(monsterPos, current3MapP, 20, 20, "left", 0))
            {
                    movementMonster.x = -51;
            }
    }

    if (player1.animatedSprite.getGlobalBounds().left + player1.animatedSprite.getGlobalBounds().width > monster1.animatedSprite.getGlobalBounds().left + monster1.animatedSprite.getGlobalBounds().width)
    {
            if(!CollisionsDetection::collisionsPlayerWall(monsterPos, current2MapP, 20, 20, "right", 0) && !CollisionsDetection::collisionsPlayerWall(monsterPos, current3MapP, 20, 20, "right", 0))
            {
                    movementMonster.x = +51;
            }
    }
    if (player1.animatedSprite.getGlobalBounds().top < monster1.animatedSprite.getGlobalBounds().top)
    {
            if(!CollisionsDetection::collisionsPlayerWall(monsterPos, current2MapP, 20, 20, "up", 0) && !CollisionsDetection::collisionsPlayerWall(monsterPos, current3MapP, 20, 20, "up", 0))
            {
                    movementMonster.y = -50;
            }
    }
    if (player1.animatedSprite.getGlobalBounds().top + player1.animatedSprite.getGlobalBounds().height > monster1.animatedSprite.getGlobalBounds().top + monster1.animatedSprite.getGlobalBounds().height)
    {
            if(!CollisionsDetection::collisionsPlayerWall(monsterPos, current2MapP, 20, 20, "down", 0) && !CollisionsDetection::collisionsPlayerWall(monsterPos, current3MapP, 20, 20, "down", 0))
            {
                    movementMonster.y = +50;
            }
    }
    int goLeft = player1.animatedSprite.getGlobalBounds().left - monster1.animatedSprite.getGlobalBounds().left;
    if (goLeft < 0)
    {
            monster1.currentAnimation = &monster1.walkingAnimationLeft;
            goLeft = -goLeft;
    }
    else monster1.currentAnimation = &monster1.walkingAnimationRight;

    int goTop  = player1.animatedSprite.getGlobalBounds().top - monster1.animatedSprite.getGlobalBounds().top;
    if (goTop < 0)
    {
            goTop = -goTop;
            if (goLeft < goTop) 
            {
                    monster1.currentAnimation = &monster1.walkingAnimationUp;
                    return;
            }
    }
    if (goLeft < goTop) monster1.currentAnimation = &monster1.walkingAnimationDown;
    // else monster1.currentAnimation = &monster1.walkingAnimationDown;
}
