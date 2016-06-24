#ifndef COLLISIONS_H
#define COLLISIONS_H

#include <SFML/Graphics.hpp>
#include <string>
#include "creature.h"

class CollisionsDetection
{
public:
    CollisionsDetection();

    int collisionsPlayerWall(sf::Vector2f &playerPos, int (levelXMap)[400], unsigned int width, unsigned int height, std::string direction, bool catchObj);

    int playerTakeObj(sf::Vector2f &playerPos, int (levelXMap)[400], unsigned int width, unsigned int height, std::string direction);

    int playerEnemies(sf::Vector2f &playerPos, sf::Vector2f &enemiesPos);

    int playerEnemies(sf::Vector2f &movements, Creature &monster1, Creature &player1);
    int playerEnemies(sf::Vector2f &movements, sf::FloatRect mFR, sf::FloatRect pFR);

    void enemiesMove(sf::Vector2f &movementMonster, Creature &player1, Creature &monster1, int (current2Map)[400], int (current3Map)[400]);
private:
    // sf::Vector2f playerPos;
    // int &levelXMap[];
    
};
#endif
