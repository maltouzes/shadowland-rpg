#ifndef MAP_MANAGER_H
#define MAP_MANAGER_H

#include <algorithm>
#include <cstring>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

class MapManager
{
public:
    MapManager();

    void setVector(std::vector<int>& level0, std::vector<int>& level1, std::vector<int>& level2, std::vector<int>& level3, std::vector<int>& level4, std::string& background, std::string& backgroundup, std::string& block, std::string& obj, std::string& hide, std::string& filename);

    std::string getFileName();
    std::string getBackground();
    std::string getBackgroundUp();
    std::string getBlock();
    std::string getObj();
    int getNumLayer();
    void initLayerName(std::string filename);
    std::string getLayerName(int numLayer);
    int getWidth();
    int getHeight();

private:
    std::string layer;
    std::string line;
    std::string line2;
    int numLine;
    int lineOnlyWithNumbers;
    std::ifstream myFile;
    std::ifstream myFile1;
    std::ifstream myFile2;
    int numberOfLines;
    std::string m_fileName;
    std::string m_background;
    std::string m_backgroundUp;
    std::string m_block;
    std::string m_obj;
    std::string m_hide; // need to implement hiden obj
    int m_numLayer;
    std::size_t posName;
    std::size_t posWidth;
    int lengthLayerName;
    std::string layerName;
    int switchLayerName;
    std::string layer1Name;
    std::string layer2Name;
    std::string layer3Name;
    std::string layer4Name;
    std::string layer5Name;

    std::size_t posEnd;
    int mapWidth;
    int mapHeight;
    std::string stringMapWidth;
    std::string stringMapHeight;
};

#endif
