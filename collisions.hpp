#ifndef COLLISIONS_hpp
#define COLLISIONS_HP

#include <SFML/Graphics.hpp>
#include <string>

class CollisionsDetection
{
public:
    CollisionsDetection();

    bool collisionsPlayerWall(sf::Vector2f &playerPos, int (levelXMap)[400], unsigned int width, unsigned int height, std::string direction);

private:
    // sf::Vector2f playerPos;
    // int &levelXMap[];
    
};
#endif
