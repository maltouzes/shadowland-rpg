#include <string>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include "game.hpp"
#include "item.hpp"

Game::Game()
: mWindow(sf::VideoMode(640, 480), "ShadowLand")
{

    sf::Clock frameClock;
    if(!tBackground.loadFromFile("Asset/background.png"))
    {
        std::cout << "Failed to load background" << std::endl;
    }
    sBackground.setTexture(tBackground);
    sBackground.setScale(2, 2);
    Item item;
}

void Game::run()
{
        mWindow.setFramerateLimit(60);
        while(mWindow.isOpen())
        {
                 processEvents();
                 render();
                 //Render render();
                 // render.render();
        }
}

void Game::processEvents()
{
            sf::Event event;
            while(Game::mWindow.pollEvent(event))
            {
                if(event.key.code == sf::Keyboard::Escape) mWindow.close();
                if(event.type == sf::Event::Closed) mWindow.close();
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
                {
                    Game::isSpriteClicked(Game::item.sItem);
                    //Game::getItem();
                }
            }
}

void Game::render()
{
            mWindow.clear();
            mWindow.draw(sBackground);
            mWindow.draw(Game::item.sItem);
            mWindow.display();
}

bool Game::isSpriteClicked (sf::Sprite& spr)
{

    if(sf::Mouse::getPosition(mWindow).x > spr.getGlobalBounds().left 
           && sf::Mouse::getPosition(mWindow).x < (spr.getGlobalBounds().left + spr.getGlobalBounds().width) 
           && sf::Mouse::getPosition(mWindow).y > spr.getGlobalBounds().top 
           && sf::Mouse::getPosition(mWindow).y < (spr.getGlobalBounds().top + spr.getGlobalBounds().height))
    {
            item.call();
    }
}
