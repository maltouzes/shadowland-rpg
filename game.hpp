#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

#include "monster.hpp"

class Game
{
public:
        Game();
        void run();
        sf::RenderWindow mWindow;
        Monster monster;

private:
        void render();
        void processEvents();
        bool isSpriteClicked(sf::Sprite& spr);
//        void getItem();

private:
        sf::Texture tBackground;
        sf::Sprite sBackground;
};

#endif
