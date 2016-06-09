#include "inventory.h"
#include <iostream>

Inventory::Inventory()
{
    this->maxObject = 20;
}

int Inventory::printInventory()
{

    for(const auto &elem : this->m_inventory)
    {
        std::cout << elem.first << " " << elem.second << std::endl;
    }
    return 0;
   /* for(auto it = m_inventory.cbegin(); it != m_inventory.cend(); ++it)
    {
        std::cout << it->first << ": " << it->second << std::endl;
    }*/
}

int Inventory::getNumberObject(const int anArray[])
{
    int numElement{0};
    for (int i{0}; i < sizeof(anArray); i++)
    {
            if (anArray[i] != 0) numElement += 1;
    }
    return numElement;
}
