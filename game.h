#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

#include "Animation.hpp"
#include "AnimatedSprite.hpp"
#include "tilemap.cpp"

class Game
{
public:
        Game();
        void run();
        sf::RenderWindow window;
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

        TileMap map1_0;
        TileMap map1_1;
        TileMap map1_2;
        TileMap map1_3;
        TileMap map1_4;

        TileMap inventoryMap;

private:
        sf::Texture tBackground;
        sf::Texture tAnimation;
        sf::Texture tInventory;
        sf::Sprite sBackground;
        sf::Sprite sInventory;
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
        bool levelNumber;
        bool showInventory;
        sf::FloatRect posInventory;
};

#endif
