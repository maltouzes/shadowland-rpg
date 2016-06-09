#ifndef INVENTORY_H
#define INVENTORY_H

#include <iostream>
#include <map>
#include <string>

class Inventory
{
public:
    Inventory();
    int printInventory();
    int getNumberObject(const int anArray[]);

public:
    std::map<std::string, int> m_inventory;
    int numberObject;
    int maxObject;

private:
};

#endif
