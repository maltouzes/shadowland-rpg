#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

#include "item.hpp"
#include "Animation.hpp"
#include "AnimatedSprite.hpp"

class Game
{
public:
        Game();
        void run();
        sf::RenderWindow window;
        Item item;
        Animation animation;
        Animation* currentAnimation;
        AnimatedSprite animatedSprite;
        sf::Clock frameClock;
        sf::Vector2i screenDimensions;
        sf::Vector2f movement;
        sf::Time frameTime;
        void render();

private:
        void processEvents();
        bool isSpriteClicked(sf::Sprite& spr);

private:
        sf::Texture tBackground;
        sf::Texture tAnimation;
        sf::Sprite sBackground;
};

#endif
