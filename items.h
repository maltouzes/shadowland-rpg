#ifndef ITEMS_H
#define ITEMS_H

#include <string>
#include <map>

class Items
{
public:
        Items();
        int readItems();
        std::string translateObj(int num);

public:
        std::map<std::map<std::string, std::string>, int> itemNumber;

};

#endif
