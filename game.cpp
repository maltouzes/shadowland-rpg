#include <string>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include "game.hpp"
#include "item.hpp"
#include "Animation.hpp"
#include "AnimatedSprite.hpp"

Game::Game()
: window(sf::VideoMode(640, 480), "ShadowLand")
{

}

void Game::run()
{
    // Two way to make view
    // create a view with the rectangular area of the 2D world to show
    //sf::View view1(sf::FloatRect(640, 480, 300, 200));
    // create a view with its center and size
    sf::View view1(sf::Vector2f(120, 240), sf::Vector2f(640, 480));
    // setup window

    sf::Vector2i screenDimensions(640,480);
    //sf::RenderWindow window(sf::VideoMode(screenDimensions.x, screenDimensions.y), "Animations!");
    window.setFramerateLimit(60);
    window.setView(view1);

    // load texture (spritesheet)
    sf::Texture texture;
    if (!texture.loadFromFile("Asset/player.png"))
    {
        std::cout << "Failed to load player spritesheet!" << std::endl;
    }

    // set up the animations for all four directions (set spritesheet and push frames)
    Animation walkingAnimationDown;
    walkingAnimationDown.setSpriteSheet(texture);
    walkingAnimationDown.addFrame(sf::IntRect(32, 0, 32, 32));
    walkingAnimationDown.addFrame(sf::IntRect(64, 0, 32, 32));
    walkingAnimationDown.addFrame(sf::IntRect(32, 0, 32, 32));
    walkingAnimationDown.addFrame(sf::IntRect( 0, 0, 32, 32));

    Animation walkingAnimationLeft;
    walkingAnimationLeft.setSpriteSheet(texture);
    walkingAnimationLeft.addFrame(sf::IntRect(32, 32, 32, 32));
    walkingAnimationLeft.addFrame(sf::IntRect(64, 32, 32, 32));
    walkingAnimationLeft.addFrame(sf::IntRect(32, 32, 32, 32));
    walkingAnimationLeft.addFrame(sf::IntRect( 0, 32, 32, 32));

    Animation walkingAnimationRight;
    walkingAnimationRight.setSpriteSheet(texture);
    walkingAnimationRight.addFrame(sf::IntRect(32, 64, 32, 32));
    walkingAnimationRight.addFrame(sf::IntRect(64, 64, 32, 32));
    walkingAnimationRight.addFrame(sf::IntRect(32, 64, 32, 32));
    walkingAnimationRight.addFrame(sf::IntRect( 0, 64, 32, 32));

    Animation walkingAnimationUp;
    walkingAnimationUp.setSpriteSheet(texture);
    walkingAnimationUp.addFrame(sf::IntRect(32, 96, 32, 32));
    walkingAnimationUp.addFrame(sf::IntRect(64, 96, 32, 32));
    walkingAnimationUp.addFrame(sf::IntRect(32, 96, 32, 32));
    walkingAnimationUp.addFrame(sf::IntRect( 0, 96, 32, 32));

    Animation* currentAnimation = &walkingAnimationDown;

    // set up AnimatedSprite
    AnimatedSprite animatedSprite(sf::seconds(0.2), true, false);
    animatedSprite.setPosition(sf::Vector2f(sf::Vector2i(640, 680)/ 2));
    animatedSprite.setScale(1, 1);

    sf::Clock frameClock;
    float speed = 80.f;
    bool noKeyWasPressed = true;
    if(!tBackground.loadFromFile("Asset/auberge-outside.png"))
    {
        std::cout << "Failed to load background" << std::endl;
    }
 
    sBackground.setTexture(tBackground);
    sBackground.setScale(0.5, 0.5);


    while(window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
                window.close();
        }

        sf::Time frameTime = frameClock.restart();

        // if a key was pressed set the correct animation and move correctly
        sf::Vector2f movement(0.f, 0.f);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
        {
            currentAnimation = &walkingAnimationUp;
            movement.y -= speed;
            noKeyWasPressed = false;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        {
            currentAnimation = &walkingAnimationDown;
            movement.y += speed;
            noKeyWasPressed = false;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
        {
            currentAnimation = &walkingAnimationLeft;
            movement.x -= speed;
            noKeyWasPressed = false;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
            currentAnimation = &walkingAnimationRight;
            movement.x += speed;
            noKeyWasPressed = false;
        }
        animatedSprite.play(*currentAnimation);
        animatedSprite.move(movement * frameTime.asSeconds());
        view1.setCenter(animatedSprite.getPosition());
        //view1.setCenter(400, 300);
        window.setView(view1);

        // if no key was pressed stop the animation
        if (noKeyWasPressed)
        {
            animatedSprite.stop();
        }
        noKeyWasPressed = true;

        // update AnimatedSprite
        animatedSprite.update(frameTime);

        // draw
        window.clear();
        window.draw(sBackground);
        window.draw(animatedSprite);
        window.display();
    }
}

void Game::processEvents()
{
            sf::Event event;
            while(Game::window.pollEvent(event))
            {
                if(event.key.code == sf::Keyboard::Escape) window.close();
                if(event.type == sf::Event::Closed) window.close();

                if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
                {
                    //Game::isSpriteClicked(Game::item.sItem);
                }
            }
}

void Game::render()
{
            window.clear();
            //window.draw(sBackground);
            window.draw(animatedSprite);
            window.display();
}

bool Game::isSpriteClicked (sf::Sprite& spr)
{

    if(sf::Mouse::getPosition(window).x > spr.getGlobalBounds().left 
           && sf::Mouse::getPosition(window).x < (spr.getGlobalBounds().left + spr.getGlobalBounds().width) 
           && sf::Mouse::getPosition(window).y > spr.getGlobalBounds().top 
           && sf::Mouse::getPosition(window).y < (spr.getGlobalBounds().top + spr.getGlobalBounds().height))
    {
            item.call();
    }
}
