#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

#include "item.hpp"
#include "Animation.hpp"
#include "AnimatedSprite.hpp"
#include "tilemap.cpp"

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

public:
        TileMap map0;
        TileMap map1;
        TileMap map2;
        TileMap map3;
        TileMap map4;
private:
        sf::Texture tBackground;
        sf::Texture tAnimation;
        sf::Sprite sBackground;
        sf::Image icon;
        sf::Vector2f vSize;

        std::vector<int> level0;
        std::vector<int> level1;
        std::vector<int> level2;
        std::vector<int> level3;
        std::string fileTmx;
        std::string layer0;
        std::string layer1;
        std::string layer2;
        std::string layer3;
        int level[];
};

#endif
