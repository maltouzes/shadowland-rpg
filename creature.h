#ifndef CREATURE_H
#define CREATURE_H

#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Time.hpp>
#include "Animation.hpp"
#include "AnimatedSprite.hpp"
#include "entity.h"

class Creature : public Entity
{
public:
    Creature(std::string mId, std::string textureLFF, double scale = 1, int health = 1);
    void printHealth() const;
    int getHealth();

public:
   Animation walkingAnimationDown;
   Animation walkingAnimationLeft;
   Animation walkingAnimationRight;
   Animation walkingAnimationUp;
   Animation* currentAnimation;

   AnimatedSprite animatedSprite;

   sf::Texture texture;

   bool touched;
   sf::Vector2f oldPosition;
   int ejectedDir;

private:
   int health;

};

#endif
