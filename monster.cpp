#include <SFML/Graphics.hpp>
#include <iostream>
#include "monster.hpp"

Monster::Monster()
{
    if(!tMonster.loadFromFile("Asset/monster.png"))
    {
        std::cout << "Failed to load monster.png" << std::endl;
    }
    sMonster.setTexture(tMonster);
    sMonster.setScale(0.3, 0.3);
}
