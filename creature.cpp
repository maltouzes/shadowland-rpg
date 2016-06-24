#include "creature.h"
#include "Animation.hpp"

Creature::Creature(std::string mId, std::string textureLFF, double scale, int mhealth) : Entity(mId)
{
    oldPosition.x = 0.f;
    oldPosition.y = 0.f;
    touched = false;
    this->health = mhealth;
    if (!texture.loadFromFile(textureLFF))
    {
        std::cout << "Failed to load " << this->getId() << " spritesheet" << std::endl;
    }

    walkingAnimationDown.setSpriteSheet(texture);
    walkingAnimationDown.addFrame(sf::IntRect(32, 0, 32, 32));
    walkingAnimationDown.addFrame(sf::IntRect(64, 0, 32, 32));
    walkingAnimationDown.addFrame(sf::IntRect(32, 0, 32, 32));
    walkingAnimationDown.addFrame(sf::IntRect(0, 0, 32, 32));

    walkingAnimationLeft.setSpriteSheet(texture);
    walkingAnimationLeft.addFrame(sf::IntRect(32, 32, 32, 32));
    walkingAnimationLeft.addFrame(sf::IntRect(64, 32, 32, 32));
    walkingAnimationLeft.addFrame(sf::IntRect(32, 32, 32, 32));
    walkingAnimationLeft.addFrame(sf::IntRect(0, 32, 32, 32));

    walkingAnimationRight.setSpriteSheet(texture);
    walkingAnimationRight.addFrame(sf::IntRect(32, 64, 32, 32));
    walkingAnimationRight.addFrame(sf::IntRect(64, 64, 32, 32));
    walkingAnimationRight.addFrame(sf::IntRect(32, 64, 32, 32));
    walkingAnimationRight.addFrame(sf::IntRect(0, 64, 32, 32));

    walkingAnimationUp.setSpriteSheet(texture);
    walkingAnimationUp.addFrame(sf::IntRect(32, 96, 32, 32));
    walkingAnimationUp.addFrame(sf::IntRect(64, 96, 32, 32));
    walkingAnimationUp.addFrame(sf::IntRect(32, 96, 32, 32));
    walkingAnimationUp.addFrame(sf::IntRect(0, 96, 32, 32));

    currentAnimation = &walkingAnimationUp; //currentAnimation*

    animatedSprite.setFrameTime(sf::seconds(0.2));
    animatedSprite.play();
    animatedSprite.setLooped(true);
    animatedSprite.setScale(scale, scale);
    animatedSprite.setPosition(sf::Vector2f(sf::Vector2i(900, 1600)/ 2));
}


void Creature::printHealth() const
{
    std::cout << this->getId() << " " << this->health << " HP" << std::endl;
}

int Creature::getHealth()
{
        return this->health;
}
