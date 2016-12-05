#include <fstream>
#include <iostream>
#include <string>

#include "items.h"

Items::Items()
{
}

int Items::readItems()
{
    std::cout << "ok" << std::endl;
    // std::string line;
    // std::ifstream myfile;
    /*myfile.open("data/itemfile");
    if (myfile.is_open())
    {
            while ( getline (myfile, line))
            {
                std::cout << line << "\n"; 
            }
            myfile.close();
    }
    else 
    {
        std::cout << "Unable to open file: itemfile" << std::endl;
    }*/

    return 0;
}

std::string Items::translateObj(int num)
{
    switch(num)
    {
        case 96:  return "barrel";
        case 97:  return "barrel";
        case 98:  return "barrel";
        case 99:  return "barrel";
        case 335: return "chest";
        case 464: return "barrel";
        case 472: return "barrel";
        case 527: return "bag";
        case 525: return "food";
        case 526: return "food";
        case 691: return "pumpkin";
        default:  return "default object";
    }

    return "none";
}
