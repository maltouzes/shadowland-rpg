#ifndef MONSTER_H
#define MONSTER_H

#include "entity.h"
#include "Animation.hpp"
#include "AnimatedSprite.hpp"
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Time.hpp>

class Monster : public Entity
{
public:
    Monster(std::string mId, std::string textureLFF);

public:
   Animation walkingAnimationDown;
   Animation walkingAnimationLeft;
   Animation walkingAnimationRight;
   Animation walkingAnimationUp;
   Animation* currentAnimation;

   AnimatedSprite animatedSprite;

   sf::Texture texture;

};

#endif
