#include <string>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include "game.hpp"
#include "monster.hpp"

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
    Monster monster;
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
                    Game::isSpriteClicked(Game::monster.sMonster);
                    //Game::getItem();
                }
            }
}

void Game::render()
{
            mWindow.clear();
            mWindow.draw(sBackground);
            mWindow.draw(Game::monster.sMonster);
            mWindow.display();
}

/*void Game::getItem()
{
    //std::cout << sf::Mouse::getPosition(mWindow) << std::endl;
    //if(sf::Vector2i localPosition = sf::Mouse::getPosition(mWindow).intersects(Game::monster.sMonster.getGlobalBounds()))
    sf::Vector2i mousePos = sf::Mouse::getPosition(mWindow);
    if(Game::monster.sMonster.getGlobalBounds().contains(sf::Mouse::getPosition()))
    {
        std::cout << "ok" << std::endl;
    }
    if(Game::monster.sMonster.getGlobalBounds().contains(mousePos))
    {
    }
}*/

bool Game::isSpriteClicked (sf::Sprite spr)
{

    if(sf::Mouse::getPosition(mWindow).x > spr.getGlobalBounds().left 
           && sf::Mouse::getPosition(mWindow).x < (spr.getGlobalBounds().left + spr.getGlobalBounds().width) 
           && sf::Mouse::getPosition(mWindow).y > spr.getGlobalBounds().top 
           && sf::Mouse::getPosition(mWindow).y < (spr.getGlobalBounds().top + spr.getGlobalBounds().height))
    {
            std::cout << "ok" << std::endl;
    }
/*    sf::Vector2i localPosition = sf::Mouse::getPosition(mWindow);
    //const sf::Input& Input = render->GetInput();
    if(localPosition.x > spr->getPosition().x 
           && localPosition.x < spr->getPosition().x + spr->getSize().x
           && localPosition.y > spr->getPosition().y 
           && localPosition.y < spr->getPosition().y + spr->getSize().y)
    {
        return true;
    }
    */
}
