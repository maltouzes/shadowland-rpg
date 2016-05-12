#include <SFML/Graphics.hpp>
#include <iostream>
#include "item.hpp"
#include <string>

Item::Item()
{
    if(!tItem.loadFromFile("Asset/item.png"))
    {
        std::cout << "Failed to load item.png" << std::endl;
    }
    sItem.setTexture(tItem);
    sItem.setScale(0.3, 0.3);
}

int Item::call()
{
        std::cout << "item" << std::endl;
        return 0;
}
