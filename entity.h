#ifndef ENTITY_H
#define ENTITY_H

#include <iostream>

class Entity
{
public:
        Entity(std::string id)
        {
                this->id = id;
        }

        virtual std::string getId() const { return this->id; }
        virtual void printId() const { std::cout << this->id << std::endl; }

private:
        std::string id;
};

#endif
