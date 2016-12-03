#include "Animation.hpp"
#include "creature.h"

Creature::Creature(std::string mId, std::string textureLFF, double scale, int mhealth, const int width, const int height) : Entity(mId)
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
    walkingAnimationDown.addFrame(sf::IntRect(width, 0, width, height));
    walkingAnimationDown.addFrame(sf::IntRect(width*2, 0, width, height));
    walkingAnimationDown.addFrame(sf::IntRect(width, 0, width, height));
    walkingAnimationDown.addFrame(sf::IntRect(0, 0, width, height));

    walkingAnimationLeft.setSpriteSheet(texture);
    walkingAnimationLeft.addFrame(sf::IntRect(width, height, width, height));
    walkingAnimationLeft.addFrame(sf::IntRect(width*2, height, width, height));
    walkingAnimationLeft.addFrame(sf::IntRect(width, height, width, height));
    walkingAnimationLeft.addFrame(sf::IntRect(0, height, width, height));

    walkingAnimationRight.setSpriteSheet(texture);
    walkingAnimationRight.addFrame(sf::IntRect(width, height*2, width, height));
    walkingAnimationRight.addFrame(sf::IntRect(width*2, height*2, width, height));
    walkingAnimationRight.addFrame(sf::IntRect(width, height*2, width, height));
    walkingAnimationRight.addFrame(sf::IntRect(0, height*2, width, height));

    walkingAnimationUp.setSpriteSheet(texture);
    walkingAnimationUp.addFrame(sf::IntRect(width, height*3, width, height));
    walkingAnimationUp.addFrame(sf::IntRect(width*2, height*3, width, height));
    walkingAnimationUp.addFrame(sf::IntRect(width, height*3, width, height));
    walkingAnimationUp.addFrame(sf::IntRect(0, height*3, width, height));

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
