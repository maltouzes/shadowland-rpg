#include <algorithm>
#include <cstring>
#include <fstream>
#include <iostream>
#include <string>
#include "map_manager.h"

#include <typeinfo>
MapManager::MapManager() :
        m_fileName("none"), m_background("none"), m_backgroundUp("none"), m_block("none"), m_obj("none"), m_numLayer(0)
{

}

void MapManager::setVector(std::vector<int>& level0, std::vector<int>& level1, std::vector<int>& level2, std::vector<int>& level3, std::vector<int>& level4, std::string& background, std::string& backgroundup, std::string& block, std::string& obj, std::string& hide, std::string& fileName)
{
  m_fileName = fileName;
  m_background = background;
  m_backgroundUp = backgroundup;
  m_block = block;
  m_obj = obj;
  m_hide = hide;
  MapManager::mapHeight = 0;
  MapManager::mapWidth = 0;
  getWidth();
  getHeight();

  myFile.open(fileName.c_str());
  while ( getline (myFile,line) )
  {
      if(line.find("layer name=") != std::string::npos) this->m_numLayer += 1;
  }
  myFile.close();
  

  myFile.open(fileName.c_str());

  numberOfLines = std::count(std::istreambuf_iterator<char>(myFile), 
                                         std::istreambuf_iterator<char>(), '\n');
  myFile.close();
  myFile.open(fileName.c_str());
  layer = "background";
  char chars[] = "abcdefghijklmnopqrstuvwxyzCUTF?é_()-.=/ <>\"";

  if (myFile.is_open())
  {
    numLine = 0;

    while ( getline (myFile,line) )
    {

    for (unsigned int i = 0 ; i < strlen(chars); ++i)
    {
    if(line.find(backgroundup) != std::string::npos) layer = "backgroundup";
    if(line.find(block) != std::string::npos) layer = "block";
    if(line.find(obj) != std::string::npos) layer = "obj";
    line.erase(std::remove(line.begin(),line.end(), chars[i]),line.end());
    }
    numLine+=1;

    lineOnlyWithNumbers= atoi(line.c_str());
    lineOnlyWithNumbers -= 1;
    if (lineOnlyWithNumbers < 0) lineOnlyWithNumbers = 0;
    if (numLine > 5 && numLine < ((mapWidth * mapHeight) + 6) && layer == background) 
    {
        level0.push_back(lineOnlyWithNumbers);
    }
    if (numLine > ((mapWidth * mapHeight) + 9) && numLine < ((mapWidth * mapHeight * 2) + 10) && layer == "backgroundup") 
    {
        level1.push_back(lineOnlyWithNumbers);
    }
    if (numLine > ((mapWidth * mapHeight * 2) + 13) && numLine < ((mapWidth * mapHeight * 3) + 14) && layer == "block") level2.push_back(lineOnlyWithNumbers);
    if (numLine > ((mapWidth * mapHeight * 3) + 17) && numLine < ((mapWidth * mapHeight * 4) + 18) && layer == "obj") level3.push_back(lineOnlyWithNumbers);
    if (numLine > ((mapWidth * mapHeight * 4) + 21) && numLine < ((mapWidth * mapHeight * 5) + 22) && layer == "obj") level4.push_back(lineOnlyWithNumbers);


    }
    myFile.close();
  }

  else std::cout << "Unable to open file"; 

}

std::string MapManager::getFileName()
{
    return this->m_fileName;
}

std::string MapManager::getBackground()
{
    // return this->m_background;
    return this->layer1Name;
}
std::string MapManager::getBackgroundUp()
{
    return this->layer2Name;
}
std::string MapManager::getBlock()
{
    return this->layer3Name;
}
std::string MapManager::getObj()
{
    return this->layer4Name;
}
int MapManager::getNumLayer()
{
    return this->m_numLayer;
}

void MapManager::initLayerName(std::string filename)
{
  MapManager::m_fileName = filename;
  myFile.open(MapManager::m_fileName.c_str());
  int switchLayerName = 1;
  while ( getline (myFile,line) )
  {
      if(line.find("layer name") != std::string::npos) 
      {
              posName = line.find("name=\"");
              posWidth = line.find("\" width=");
              posName += 6;
              lengthLayerName = posWidth - posName;
              layerName = line.substr(posName, lengthLayerName);
              if(switchLayerName == 1 && layer1Name == "") layer1Name = layerName;
              if(switchLayerName == 2 && layer1Name.compare(layerName)) layer2Name = layerName;
              if(switchLayerName == 3 && layer2Name.compare(layerName)) layer3Name = layerName;
              if(switchLayerName == 4 && layer3Name.compare(layerName)) layer4Name = layerName;
              if(switchLayerName == 5 && layer4Name.compare(layerName)) layer5Name = layerName;

              switchLayerName += 1;
      }
  }
  myFile.close();
  return;
}

std::string MapManager::getLayerName(int numLayer)
{
    switch(numLayer) 
    {
        case 1  : if(layer1Name != "") return layer1Name;
        case 2  : if(layer2Name != "") return layer2Name;
        case 3  : if(layer3Name != "") return layer3Name;
        case 4  : if(layer4Name != "") return layer4Name;
        case 5  : if(layer5Name != "") return layer5Name;

        default : return "no Layer";
    }
}

int MapManager::getWidth()
{
  myFile2.open(MapManager::m_fileName.c_str());
  while ( getline (myFile2,line) )
  {
      if(line.find("layer name") != std::string::npos && MapManager::mapWidth == 0)
      {
          posWidth = line.find("width=\"");
          std::size_t posHeight = line.find("height=\"");
          posWidth += 7; // lenght of the world in tmx file
          int lengthWidth = posHeight - posWidth - 2;
          stringMapWidth = line.substr (posWidth,lengthWidth);
          MapManager::mapWidth = std::stoi(stringMapWidth);
      }
  }
  myFile2.close();
  return 0;
}

int MapManager::getHeight()
{
  myFile1.open(MapManager::m_fileName.c_str());
  while ( getline (myFile1,line) )
  {
      if(line.find("layer name") != std::string::npos && mapHeight == 0)
      {
          std::size_t posHeight = line.find("height=\"");
          posHeight += 8;
          posEnd = line.find("\">");
          stringMapHeight = line.substr (posHeight,(posEnd - posHeight));
          MapManager::mapHeight = std::stoi(stringMapHeight);
      }
  }
  myFile1.close();
  return 0;
}

