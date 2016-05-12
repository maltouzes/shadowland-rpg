#ifndef MONSTER_HPP
#define MONSTER_HPP

#include <SFML/Graphics.hpp>
#include <string>

class Monster
{
public:
        Monster();
        sf::Texture tMonster;
        sf::Sprite sMonster;
        int call();

};

#endif
