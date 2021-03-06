#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

#include "Animation.hpp"
#include "AnimatedSprite.hpp"
#include "collisions.h"
#include "creature.h"
#include "inventory.h"
#include "items.h"
#include "entity.h"
#include "game.h"
#include "map_manager.h"

Game::Game()
// : window(sf::VideoMode(640, 480), "ShadowLand")
: window(sf::VideoMode(1280, 960), "ShadowLand")
{
    icon.loadFromFile("Asset/icon.png");
    window.setIcon(32, 32, icon.getPixelsPtr());
    showInventory = 0;

}
// To change the map size:
// 1) change view1
// 2) change levlxMap[]
// 3) chage mapx.load()
// 4) change sf::Keyboard::V
void Game::run()
{
     if (!sf::Shader::isAvailable())
     {
         std::cout << "can't use shaders" << std::endl;
     }

     sf::Shader shader;
     sf::Shader shader2;
     if (!shader.loadFromFile("shaders/fragment.frag", sf::Shader::Fragment))
     {
         std::cout << "load shader error" << std::endl;
     }

     if (!shader2.loadFromFile("shaders/vertext.vert", sf::Shader::Vertex))
     {
         std::cout << "load shader2 error" << std::endl;
     }

     if (sf::Joystick::isConnected(0))
     {
             std::cout << "joystick number 0 is connected" << std::endl;
             // check how many buttons joystick number 0 has
             unsigned int buttonCount = sf::Joystick::getButtonCount(0);
             std::cout << buttonCount << std::endl;
             // // check if joystick number 0 has a Z axis
             bool hasZ = sf::Joystick::hasAxis(0, sf::Joystick::Z);
             std::cout << hasZ << std::endl;
     }
    sf::Clock clock;
    sf::Clock clock2;
    levelNumber = false;
    // Two way to make view
    // create a view with the rectangular area of the 2D world to show
    //sf::View view1(sf::FloatRect(640, 480, 300, 200));
    // create a view with its center and size
    sf::View view1(sf::Vector2f(120, 240), sf::Vector2f(640, 480));
    //sf::View view1(sf::Vector2f(120, 240), sf::Vector2f(160, 120)); // change the second if the map is bigger/smaller
    // setup window

    screenDimensions = sf::Vector2i(640,480);
    //sf::RenderWindow window(sf::VideoMode(screenDimensions.x, screenDimensions.y), "Animations!");
    window.setVerticalSyncEnabled(true);
    // window.setFramerateLimit(60);
    window.setView(view1);

    // load texture (spritesheet)
    sf::Texture texture;
    if (!texture.loadFromFile("Asset/player.png"))
    {
        std::cout << "Failed to load player spritesheet!" << std::endl;
    }

    // set up the animations for all four directions (set spritesheet and push frames)
    Inventory pInventory;
    Items items;

    Creature monster1("monster1", "Asset/gorksprite96-128.png", 1.4, 1, 32, 32);
    monster1.printId();
    monster1.printHealth();

    Creature player1("player1", "Asset/player.png", 1.4, 6, 32, 32);
    player1.printHealth();

    float speed = 60.f; // 80.f
    bool noKeyWasPressed = true;
    if(!tBackground.loadFromFile("Asset/background-dark.png"))
    {
        std::cout << "Failed to load background" << std::endl;
    }

    if(!tInventory.loadFromFile("Asset/inventory.png"))
    {

        std::cout << "Failed to load inventory" << std::endl;
    }

    sInventory.setTexture(tInventory);
    posInventory= sInventory.getGlobalBounds(); // inventory.width (float rect)

    // map and map_manager
    std::vector<int> level1_0;
    std::vector<int> level1_1;
    std::vector<int> level1_2;
    std::vector<int> level1_3;
    std::vector<int> level1_4;

    fileTmx = "Asset/auberge-outside-ok.tmx";
    fileTmx2 = "Asset/auberge-new.tmx";

    MapManager mapManager;
    mapManager.initLayerName(fileTmx);

    MapManager mapManager2;
    mapManager2.initLayerName(fileTmx2);

    layer0 = mapManager.getLayerName(1);
    layer1 = mapManager.getLayerName(2);
    layer2 = mapManager.getLayerName(3);
    layer3 = mapManager.getLayerName(4);
    layer4 = mapManager.getLayerName(5);

    std::string layer1_0 = mapManager2.getLayerName(1);
    std::string layer1_1 = mapManager2.getLayerName(2);
    std::string layer1_2 = mapManager2.getLayerName(3);
    std::string layer1_3 = mapManager2.getLayerName(4);
    std::string layer1_4 = mapManager2.getLayerName(5);

    mapManager.setVector(level0, level1, level2, level3, level4, layer0, layer1, layer2, layer3, layer4, fileTmx);

    mapManager2.setVector(level1_0, level1_1, level1_2, level1_3, level1_4, layer1_0, layer1_1, layer1_2, layer1_3, layer1_4, fileTmx2);

    // std::vector<double> v;
    // double* a = &v[0];
    int level0Map[400]; // 1600
    int level1Map[400];
    int level2Map[400];
    int level3Map[400];
    int level4Map[400];
    std::copy(level0.begin(), level0.end(), level0Map);
    std::copy(level1.begin(), level1.end(), level1Map);
    std::copy(level2.begin(), level2.end(), level2Map);
    std::copy(level3.begin(), level3.end(), level3Map);
    std::copy(level4.begin(), level4.end(), level4Map);

    int level1_0Map[400]; // 1600
    int level1_1Map[400];
    int level1_2Map[400];
    int level1_3Map[400];
    int level1_4Map[400];
    std::copy(level1_0.begin(), level1_0.end(), level1_0Map);
    std::copy(level1_1.begin(), level1_1.end(), level1_1Map);
    std::copy(level1_2.begin(), level1_2.end(), level1_2Map);
    std::copy(level1_3.begin(), level1_3.end(), level1_3Map);
    std::copy(level1_4.begin(), level1_4.end(), level1_4Map);

    int inventoryArray[20] = {};

    int * current3Map;
    int * current2Map;
    int * current4Map;
    current3Map = level3Map;
    current2Map = level2Map;
    current4Map = level4Map;
    // int levelHeight{20};
    // int levelWidth{20};

    int mapScale{4};
    int mapWidth{20};
    // int mapHeight{20};

    if(!inventoryMap.load("Asset/tile2map16.png", sf::Vector2u(16, 16), inventoryArray, 4, 5)) // 10, 8
    {
        std::cout << "Can't add inventory" << std::endl;
    }

    // Not 100! 20
    if(!map0.load("Asset/tile2map16.png", sf::Vector2u(16, 16), level0Map, 20, 20))
    {
        std::cout << "Can't add objects" << std::endl;
    }
    if(!map1.load("Asset/tile2map16.png", sf::Vector2u(16, 16), level1Map, 20, 20))
    {
        std::cout << "Can't add objects" << std::endl;
    }
    if(!map2.load("Asset/tile2map16.png", sf::Vector2u(16, 16), level2Map, 20, 20))
    {
        std::cout << "Can't add objects" << std::endl;
    }
    if(!map3.load("Asset/tile2map16.png", sf::Vector2u(16, 16), level3Map, 20, 20))
    {
        std::cout << "Can't add objects" << std::endl;
    }
    if(!map4.load("Asset/tile2map16.png", sf::Vector2u(16, 16), level4Map, 20, 20))
    {
        std::cout << "Can't add objects" << std::endl;
    }

    if(!map1_0.load("Asset/tile2map16.png", sf::Vector2u(16, 16), level1_0Map, 20, 20))
    {
        std::cout << "Can't add objects" << std::endl;
    }
    if(!map1_1.load("Asset/tile2map16.png", sf::Vector2u(16, 16), level1_1Map, 20, 20))
    {
        std::cout << "Can't add objects" << std::endl;
    }
    if(!map1_2.load("Asset/tile2map16.png", sf::Vector2u(16, 16), level1_2Map, 20, 20))
    {
        std::cout << "Can't add objects" << std::endl;
    }
    if(!map1_3.load("Asset/tile2map16.png", sf::Vector2u(16, 16), level1_3Map, 20, 20))
    {
        std::cout << "Can't add objects" << std::endl;
    }
    if(!map1_4.load("Asset/tile2map16.png", sf::Vector2u(16, 16), level1_4Map, 20, 20))
    {
        std::cout << "Can't add objects" << std::endl;
    }

    /* map0.m_tileset.setSmooth(0);
     map1.m_tileset.setSmooth(0);
    map2.m_tileset.setSmooth(0);
    map3.m_tileset.setSmooth(0);
    map4.m_tileset.setSmooth(0);*/

    map0.setScale(mapScale, mapScale);
    map1.setScale(mapScale, mapScale);
    map2.setScale(mapScale, mapScale);
    map3.setScale(mapScale, mapScale);
    map4.setScale(mapScale, mapScale);

    inventoryMap.setScale(mapScale-0.5, mapScale-0.5);

    map1_0.setScale(mapScale, mapScale);
    map1_1.setScale(mapScale, mapScale);
    map1_2.setScale(mapScale, mapScale);
    map1_3.setScale(mapScale, mapScale);
    map1_4.setScale(mapScale, mapScale);

    sBackground.setTexture(tBackground);
    //sBackground.setScale(0.5, 0.5);
    sf::FloatRect posBackground = sBackground.getGlobalBounds(); // for background.x
    float backgroundX = (posBackground.width - posBackground.left);
    float backgroundY = (posBackground.height- posBackground.top);

    CollisionsDetection collisions;


    while(window.isOpen())
    {
        sf::Time elapsed1 = clock.getElapsedTime();
        sf::Time elapsed2 = clock2.getElapsedTime();
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
                window.close();
        }

        frameTime = frameClock.restart();

        sf::Vector2f playerPos = player1.animatedSprite.getPosition();
        // if a key was pressed set the correct animation and move correctly
        movement = sf::Vector2f(0.f, 0.f);
        sf::Vector2f movementMonster(0.f, 0.f);

        if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Z) || sf::Joystick::getAxisPosition(0, sf::Joystick::Y) < -20) && playerPos.y >= 0)
        {

            if (!showInventory)
            {
            player1.currentAnimation = &player1.walkingAnimationUp;
            if(!collisions.collisionsPlayerWall(playerPos, current3Map, 20, "up", 0)
               && (!collisions.collisionsPlayerWall(playerPos, current2Map, 20, "up", 0)))
            {
                movement.y -= speed;
                noKeyWasPressed = false;
            }
            int hideObj = collisions.collisionsPlayerWall(playerPos, current4Map, 20, "up", true);
            if(hideObj)
            {
                for(int x= 0; x < 1600; x++)
                {
                    if(current4Map[x] == hideObj) // && map4.m_vertices[x*4].color.a > 168)
                    {
                        int alpha1 = map4.m_vertices[x*mapScale].color.a - 8;
                        if (alpha1 < 168) alpha1 = 168;
                        int alpha2 = map4.m_vertices[x*mapScale+1].color.a - 8;
                        if (alpha2 < 168) alpha2 = 168;
                        int alpha3 = map4.m_vertices[x*mapScale+2].color.a - 8;
                        if (alpha3 < 168) alpha3 = 168;
                        int alpha4 = map4.m_vertices[x*mapScale+3].color.a - 8;
                        if (alpha4 < 168) alpha4 = 168;

                        map4.m_vertices[(x*mapScale - (mapWidth * mapScale))].color = sf::Color(255, 255, 255, alpha1);
                        map4.m_vertices[(x)*mapScale + 1 - (mapWidth * mapScale)].color = sf::Color(255, 255, 255, alpha1);
                        map4.m_vertices[(x)*mapScale + 2 - (mapWidth * mapScale)].color = sf::Color(255, 255, 255, alpha2);
                        map4.m_vertices[(x)*mapScale + 3 - (mapWidth * mapScale)].color = sf::Color(255, 255, 255, alpha3);

                        for (int i{-1}; i < 2; i ++)
                        {
                            map4.m_vertices[(x+i)*mapScale].color = sf::Color(255, 255, 255, alpha1);
                            map4.m_vertices[(x+i)*mapScale + 1].color = sf::Color(255, 255, 255, alpha2);
                            map4.m_vertices[(x+i)*mapScale + 2].color = sf::Color(255, 255, 255, alpha3);
                            map4.m_vertices[(x+i)*mapScale + 3].color = sf::Color(255, 255, 255, alpha4);
                        }

                    }
                }
            }
            }
        }
        if ((sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Joystick::getAxisPosition(0, sf::Joystick::Y) > 20) && playerPos.y <= backgroundY - 45)
        {

            if (!showInventory)
            {
            int hideObj = collisions.collisionsPlayerWall(playerPos, current4Map, 20, "down", true);
            if(hideObj)
            {
                for(int x= 0; x < 1600; x++)
                {
                    if(current4Map[x] == hideObj && map4.m_vertices[x*4].color.a > 168)
                    {
                        int alpha1 = map4.m_vertices[x*mapScale].color.a - 8;
                        if (alpha1 < 168) alpha1 = 168;
                        int alpha2 = map4.m_vertices[x*mapScale+1].color.a - 8;
                        if (alpha2 < 168) alpha2 = 168;
                        int alpha3 = map4.m_vertices[x*mapScale+2].color.a - 8;
                        if (alpha3 < 168) alpha3 = 168;
                        int alpha4 = map4.m_vertices[x*mapScale+3].color.a - 8;
                        if (alpha4 < 168) alpha4 = 168;

                        map4.m_vertices[(x*mapScale + (mapWidth * mapScale))].color = sf::Color(255, 255, 255, alpha1);
                        map4.m_vertices[(x)*mapScale + 1 + (mapWidth * mapScale)].color = sf::Color(255, 255, 255, alpha1);
                        map4.m_vertices[(x)*mapScale + 2 + (mapWidth * mapScale)].color = sf::Color(255, 255, 255, alpha2);
                        map4.m_vertices[(x)*mapScale + 3 + (mapWidth * mapScale)].color = sf::Color(255, 255, 255, alpha3);

                        for (int i{-1}; i < 2; i++)
                        {

                            map4.m_vertices[(x+i)*mapScale].color = sf::Color(255, 255, 255, alpha1);
                            map4.m_vertices[(x+i)*mapScale + 1].color = sf::Color(255, 255, 255, alpha2);
                            map4.m_vertices[(x+i)*mapScale + 2].color = sf::Color(255, 255, 255, alpha3);
                            map4.m_vertices[(x+i)*mapScale + 3].color = sf::Color(255, 255, 255, alpha4);
                        }
                    }
                }
            }

            //currentAnimation = &walkingAnimationDown;
            player1.currentAnimation = &player1.walkingAnimationDown;
            if(!collisions.collisionsPlayerWall(playerPos, current3Map, 20, "down", 0)
               && (!collisions.collisionsPlayerWall(playerPos, current2Map, 20, "down", 0)))
            {
                movement.y += speed;
                noKeyWasPressed = false;
            }
        }
        }

        if((sf::Keyboard::isKeyPressed(sf::Keyboard::Q) || sf::Joystick::getAxisPosition(0, sf::Joystick::X) < - 20) && playerPos.x >= 0)
        {
            if (!showInventory)
            {
            player1.currentAnimation = &player1.walkingAnimationLeft;
            if(!collisions.collisionsPlayerWall(playerPos, current3Map, 20, "left", 0)
               && (!collisions.collisionsPlayerWall(playerPos, current2Map, 20, "left", 0)))
            {
                movement.x -= speed;
                noKeyWasPressed = false;
            }
            int hideObj = collisions.collisionsPlayerWall(playerPos, current4Map, 20, "left", true);
            if(hideObj)
            {
                for(int x= 0; x < 1600; x++)
                {
                    if(current4Map[x] == hideObj && map4.m_vertices[x*4].color.a > 168)
                    {
                        int alpha = map4.m_vertices[x*mapScale].color.a - 8;
                        if (alpha < 168) alpha = 168;
                        map4.m_vertices[x*mapScale - 1].color = sf::Color(255, 255, 255, alpha);
                        map4.m_vertices[x*mapScale - 2].color = sf::Color(255, 255, 255, alpha);
                        map4.m_vertices[x*mapScale - 3].color = sf::Color(255, 255, 255, alpha);
                        map4.m_vertices[x*mapScale - 4].color = sf::Color(255, 255, 255, alpha);

                        for (int i{-mapWidth * mapScale}; i < mapWidth * mapScale * 2; i+= mapWidth * mapScale)
                        {
                            map4.m_vertices[x*mapScale +i].color = sf::Color(255, 255, 255, alpha);
                            map4.m_vertices[x*mapScale + i  + 1].color = sf::Color(255, 255, 255, alpha);
                            map4.m_vertices[x*mapScale + i + 2].color = sf::Color(255, 255, 255, alpha);
                            map4.m_vertices[x*mapScale + i + 3].color = sf::Color(255, 255, 255, alpha);
                        }
                    }
                }
            }
        }
        }

        if ((sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Joystick::getAxisPosition(0, sf::Joystick::X) > 20) && playerPos.x <= backgroundX - 45)
        {
            if (!showInventory)
            {
            player1.currentAnimation = &player1.walkingAnimationRight;
            if(!collisions.collisionsPlayerWall(playerPos, current3Map, 20, "right", 0)
               && (!collisions.collisionsPlayerWall(playerPos, current2Map, 20, "right", 0)))
            {
                movement.x += speed;
                noKeyWasPressed = false;
            }
            int hideObj = collisions.collisionsPlayerWall(playerPos, current4Map, 20, "right", true);
            if(hideObj)
            {
                for(int x{0}; x < 1600; x++)
                {
                    if(current4Map[x] == hideObj) // && map4.m_vertices[x*4].color.a > 168)
                    {
                        int alpha = map4.m_vertices[x*mapScale].color.a - 8;
                        if (alpha < 168) alpha = 168;
                        map4.m_vertices[x*mapScale + 4].color = sf::Color(255, 255, 255, alpha);
                        map4.m_vertices[x*mapScale + 5].color = sf::Color(255, 255, 255, alpha);
                        map4.m_vertices[x*mapScale + 6].color = sf::Color(255, 255, 255, alpha);
                        map4.m_vertices[x*mapScale + 7].color = sf::Color(255, 255, 255, alpha);
                        for (int i{-mapWidth * mapScale}; i < mapWidth * mapScale * 2; i+= mapWidth * mapScale)
                        {
                            map4.m_vertices[x*mapScale +i].color = sf::Color(255, 255, 255, alpha);
                            map4.m_vertices[x*mapScale + i + 1].color = sf::Color(255, 255, 255, alpha);
                            map4.m_vertices[x*mapScale + i + 2].color = sf::Color(255, 255, 255, alpha);
                            map4.m_vertices[x*mapScale + i + 3].color = sf::Color(255, 255, 255, alpha);
                        }
                    }
                }
            }

        }
        }

        // Need to check if m_inventory is not full before add a new items
        if ((sf::Keyboard::isKeyPressed(sf::Keyboard::U) || sf::Joystick::isButtonPressed(0, 0)) && pInventory.numberObject < pInventory.maxObject && elapsed1.asSeconds() > float(0.2))
        {
            clock.restart();
            std::string dir{"dir"};
            if (player1.currentAnimation == &player1.walkingAnimationUp) dir = "up";
            if (player1.currentAnimation == &player1.walkingAnimationDown) dir = "down";
            if (player1.currentAnimation == &player1.walkingAnimationLeft) dir = "left";
            if (player1.currentAnimation == &player1.walkingAnimationRight) dir = "right";
            // if (currentAnimation == &walkingAnimationRight) dir = "right";
                int eraseObj = collisions.collisionsPlayerWall(playerPos, current2Map, 20, dir, true);
            if(eraseObj)
            {
                int x = collisions.playerTakeObj(playerPos, current2Map, 20);
                        pInventory.m_inventory[items.translateObj(current2Map[x])] += 1;
                        pInventory.numberObject +=1;
                        std::cout << "numberObj " << pInventory.numberObject << std::endl;
                        if (pInventory.m_inventory.find("none") != pInventory.m_inventory.end() )
                       {
                               pInventory.m_inventory.erase ("none");
                               pInventory.numberObject -=1;
                       }

                        bool found = 0;

                        if (items.translateObj(current2Map[x]).compare("none") != 0)
                        {
                        for (int newX{0}; newX < 20; newX++)
                        {
                            if (inventoryArray[newX] == 0) 
                            {
                                    found = 1;
                                    inventoryArray[newX] = eraseObj;
                            }
                            if (found == 1) break;
                        }
                        // inventoryArray[x] = eraseObj;
                        inventoryMap.load("Asset/tile2map16.png", sf::Vector2u(16, 16), inventoryArray, 4, 5);
                        }
                        current2Map[x] = 0;
                        if(levelNumber == 0)
                        {
                            map2.load("Asset/tile2map16.png", sf::Vector2u(16, 16), level2Map, 20, 20);
                        }
                        if(levelNumber == 1)
                        {
                            map1_2.load("Asset/tile2map16.png", sf::Vector2u(16, 16), level1_2Map, 20, 20);
                        }
            }

            for(auto elem : pInventory.m_inventory)
            {
                std::cout << elem.first << " " << elem.second << std::endl;
            }
            std::cout << std::endl;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::J))
        {
            for (int i{0}; i < 1600; i++)
            {
            map4.m_vertices[i].color = sf::Color(255, 255, 255, 168);
            }

        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::K))
        {
            for (int i{0}; i < 1600; i++)
            {
            map4.m_vertices[i].color = sf::Color(255, 255, 255, 255);
            }

        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::V) || sf::Joystick::isButtonPressed(0, 4))
        {
                vSize = view1.getSize();
                std::cout << vSize.x << std::endl;
                std::cout << vSize.y << std::endl;
                sf::Vector2u wSize = window.getSize();
                std::cout << wSize.x << std::endl;
                std::cout << wSize.x << std::endl;
                // if (vSize.x < 1000 && vSize.y < 1000 )
                std::cout << "playerPos x: " << playerPos.x << std::endl;
                std::cout << "playerPos y: " << playerPos.y << std::endl;
                if (vSize.x < 1000 && vSize.y < 1000 )
                {
                    view1.zoom(1.01f);
                }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::M) && elapsed1.asSeconds() > float(0.2))
        {
                std::cout << elapsed1.asSeconds() << std::endl;
                if (levelNumber == 1) levelNumber = 0;
                else levelNumber = 1;
                std::cout << "levelNumber: " << levelNumber << std::endl;
                clock.restart();
        }

        if ((sf::Keyboard::isKeyPressed(sf::Keyboard::I) || (sf::Joystick::isButtonPressed(0, 3))) && elapsed1.asSeconds() > float(0.2))
        {
            showInventory = !showInventory;
            int posX = playerPos.x - posInventory.width/2;
            int posY = playerPos.y - posInventory.height/2;

            if (posX < 0) posX = 0;
            if (posY < 0) posY = 0;
            if (posX > posBackground.width - posInventory.width) posX = posBackground.width - posInventory.width;
            if (posY > posBackground.height - posInventory.height) posY = posBackground.height - posInventory.height;

            sInventory.setPosition(sf::Vector2f(sf::Vector2i(posX, posY)));
            inventoryMap.setPosition(sf::Vector2f(sf::Vector2i(posX + 25, posY + 65)));

            clock.restart();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::RShift)) 
        {
            speed = 400.f;
        }
        else
        {
            speed = 80.f;
        }

        /*// Enemies Hit player
        sf::Vector2f enemiePos = monster1.animatedSprite.getPosition();
        if (collisions.playerEnemies(playerPos, enemiePos) && elapsed1.asSeconds() > 0.2)
        {
                clock.restart();
                int a = collisions.playerEnemies(playerPos, enemiePos);
                if (a == -96)
                {
                        movement.x -= 2000.f;
                }
                if (a == 96)
                {
                        movement.x += 1500.f;
                }
                if (a == -32)
                {
                        movement.y -= 2000.f;
                }
                if (a == 32)
                {
                        movement.y += 2000.f;
                }
        }*/

        vSize = view1.getSize();
        if (!(sf::Keyboard::isKeyPressed(sf::Keyboard::V) || sf::Joystick::isButtonPressed(0, 4)) && vSize.x > 640 && vSize.y > 480)
        // if (!sf::Keyboard::isKeyPressed(sf::Keyboard::V) && vSize.x > 160 && vSize.y > 120)
        {
                    view1.zoom(0.99f);
        }

        //animatedSprite.play(*currentAnimation);
        // animatedSprite.move(movement * frameTime.asSeconds());

        if(elapsed2.asSeconds() > 1 && !showInventory)
        {
            // std::cout << monster1.animatedSprite.getGlobalBounds().left << std::endl;
            collisions.playerEnemies(movement, monster1, player1);
            collisions.enemiesMove(movementMonster, monster1, player1, current2Map, current3Map);
        }

        // collisions.playerEnemies(movement, monster1, player1);

        player1.animatedSprite.play(*player1.currentAnimation);
        player1.animatedSprite.move(movement * frameTime.asSeconds());

        monster1.animatedSprite.move(movementMonster * frameTime.asSeconds());
        monster1.animatedSprite.play(*monster1.currentAnimation);
        //view1.setCenter(animatedSprite.getPosition());
        //view1.setCenter(400, 300);

        //sf::Vector2f viewCenter = view1.getCenter();
        //std::cout << viewCenter.x << "hehe" << std::endl;
        // here!!!!sf::Vector2f playerPos = animatedSprite.getPosition();
        // std::cout << "PlayerPos x " << playerPos.x << "PlayerPos.y " << playerPos.y << std::endl;


        view1.setCenter(player1.animatedSprite.getPosition());
        //if (playerPos.x < 320) view1.setCenter(320, playerPos.y);
        if (playerPos.x < (vSize.x / 2 )) view1.setCenter((vSize.x / 2), playerPos.y);

        if (playerPos.x > (backgroundX - (vSize.x / 2))) view1.setCenter((backgroundX - (vSize.x / 2)), playerPos.y);
        if (playerPos.y < (vSize.y / 2)) view1.setCenter(playerPos.x, (vSize.y / 2));
        if (playerPos.y > (backgroundY - vSize.y / 2)) view1.setCenter(playerPos.x, (backgroundY - (vSize.y / 2)));

        //if (playerPos.x < 320 && playerPos.y < 240) view1.setCenter(320, 240);
        if (playerPos.x < (vSize.x / 2) && playerPos.y < (vSize.y / 2)) view1.setCenter((vSize.x / 2), (vSize.y / 2));

        if (playerPos.x > (backgroundX - (vSize.x / 2)) && playerPos.y < (vSize.y / 2)) view1.setCenter((backgroundX - (vSize.x / 2)), (vSize.y / 2));
        if (playerPos.x < (vSize.x / 2) && playerPos.y > (backgroundY - (vSize.y / 2))) view1.setCenter((vSize.x / 2), (backgroundY - (vSize.y / 2)));
        if (playerPos.x > (backgroundX - (vSize.x / 2)) && playerPos.y > (backgroundY - (vSize.y / 2))) view1.setCenter((backgroundX - (vSize.x / 2)), (backgroundY - (vSize.y / 2)));

        window.setView(view1);
        // if no key was pressed stop the animation
        if (noKeyWasPressed)
        {
            player1.animatedSprite.stop();
        }
        noKeyWasPressed = true;

        // update AnimatedSprite
        // animatedSprite.update(frameTime);
        monster1.animatedSprite.update(frameTime);
        player1.animatedSprite.update(frameTime);

        // draw
        window.clear();
        if(levelNumber == 0)
        {
          current3Map = level3Map;
          current2Map = level2Map;
          window.draw(map0);
          window.draw(map1);
          window.draw(map2);
          window.draw(map3);
          window.draw(monster1.animatedSprite);
          window.draw(player1.animatedSprite);
          window.draw(map4);
        }
        else
        {
          current3Map = level1_3Map;
          current2Map = level1_2Map;
          window.draw(map1_0);
          window.draw(map1_1);
          window.draw(map1_2);
          window.draw(map1_3);
          window.draw(monster1.animatedSprite);
          window.draw(player1.animatedSprite);
          window.draw(map1_4);
        }

        if (showInventory == 1)
        {
            window.draw(sInventory);
            window.draw(inventoryMap);
        }
        window.display();
    }
}
