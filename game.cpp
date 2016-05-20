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
    sf::Image icon;
    if(!icon.loadFromFile("Asset/icon.png"));
    window.setIcon(512, 512, icon.getPixelsPtr());

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
    animatedSprite.setPosition(sf::Vector2f(sf::Vector2i(1280, 1400)/ 2));
    animatedSprite.setScale(1.4, 1.4);

    sf::Clock frameClock;
    float speed = 80.f; // 80.f
    bool noKeyWasPressed = true;
    // if(!tBackground.loadFromFile("Asset/zelda-overworld.png"))
    if(!tBackground.loadFromFile("Asset/auberge-outside.png"))
    {
        std::cout << "Failed to load background" << std::endl;
    }
 
    sBackground.setTexture(tBackground);
    //sBackground.setScale(0.5, 0.5);
    sf::FloatRect posBackground = sBackground.getGlobalBounds(); // for background.x
    float backgroundX = (posBackground.width - posBackground.left);
    float backgroundY = (posBackground.height- posBackground.top);


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

        sf::Vector2f playerPos = animatedSprite.getPosition();
        // if a key was pressed set the correct animation and move correctly
        sf::Vector2f movement(0.f, 0.f);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z) && playerPos.y >= 0)
        {
            currentAnimation = &walkingAnimationUp;
            movement.y -= speed;
            noKeyWasPressed = false;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && playerPos.y <= backgroundY - 45)
        {
            currentAnimation = &walkingAnimationDown;
            movement.y += speed;
            noKeyWasPressed = false;
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q) && playerPos.x >= 0)
        {
            currentAnimation = &walkingAnimationLeft;
            movement.x -= speed;
            noKeyWasPressed = false;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && playerPos.x <= backgroundX - 45)
        {
            currentAnimation = &walkingAnimationRight;
            movement.x += speed;
            noKeyWasPressed = false;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::V))
        {
                sf::Vector2f vSize = view1.getSize();
                std::cout << vSize.x << std::endl;
                std::cout << vSize.y << std::endl;
                sf::Vector2u wSize = window.getSize();
                std::cout << wSize.x << std::endl;
                std::cout << wSize.x << std::endl;
                if (vSize.x < 1000 && vSize.y < 1000 )
                {
                    view1.zoom(1.01f);
                }
        }
        sf::Vector2f vSize = view1.getSize();
        if (!sf::Keyboard::isKeyPressed(sf::Keyboard::V) && vSize.x > 640 && vSize.y > 480)
        {
                    view1.zoom(0.99f);
        }

        animatedSprite.play(*currentAnimation);
        animatedSprite.move(movement * frameTime.asSeconds());
        //view1.setCenter(animatedSprite.getPosition());
        //view1.setCenter(400, 300);

        //sf::Vector2f viewCenter = view1.getCenter();
        //std::cout << viewCenter.x << "hehe" << std::endl;
        // here!!!!sf::Vector2f playerPos = animatedSprite.getPosition();
        // std::cout << "PlayerPos x " << playerPos.x << "PlayerPos.y " << playerPos.y << std::endl;


        view1.setCenter(animatedSprite.getPosition());
        //if (playerPos.x < 320) view1.setCenter(320, playerPos.y);
        if (playerPos.x < (vSize.x / 2 )) view1.setCenter((vSize.x / 2), playerPos.y);

        if (playerPos.x > (backgroundX - (vSize.x / 2))) view1.setCenter((backgroundX - (vSize.x / 2)), playerPos.y);
        if (playerPos.y < (vSize.y / 2)) view1.setCenter(playerPos.x, (vSize.y / 2));
        if (playerPos.y > (backgroundY - vSize.y / 2)) view1.setCenter(playerPos.x, (backgroundY - (vSize.y / 2)));

        //if (playerPos.x < 320 && playerPos.y < 240) view1.setCenter(320, 240);
        if (playerPos.x < (vSize.x / 2) && playerPos.y < (vSize.y / 2)) view1.setCenter((vSize.x / 2), (vSize.y / 2));

        if (playerPos.x > (backgroundX - (vSize.x / 2)) && playerPos.y < (vSize.y / 2)) view1.setCenter((backgroundX - (vSize.x / 2)), (vSize.y / 2));
        if (playerPos.x < (vSize.x / 2) && playerPos.y > (backgroundY - (vSize.y / 2))) view1.setCenter((vSize.x / 2), (backgroundY - (vSize.y / 2)));
        if (playerPos.x > (backgroundX - (vSize.x / 2)) && playerPos.y > (backgroundY - (vSize.y / 2))) view1.setCenter((backgroundX - (vSize.x / 2)), (backgroundY - (vSize.y / 2)));

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
