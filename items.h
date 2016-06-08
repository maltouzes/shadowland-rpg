#ifndef ITEMS_H
#define ITEMS_H

#include <string>
#include <map>

class Items
{
public:
        Items();
        int readItems();

public:
        std::map<std::map<std::string, std::string>, int> itemNumber;

};

#endif
