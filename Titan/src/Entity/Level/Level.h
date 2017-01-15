#pragma once

#include <SFML/Graphics.hpp>

#include <string>
#include <vector>
#include <map>
#include <iostream>

#include "tinyxml.h"

struct Object
{
    int getPropertyInt(std::string name);

    float getPropertyFloat(std::string name);

    std::string getPropertyString(std::string name);

    std::string name;
    std::string type;
    sf::Rect<float> rect;
    std::map<std::string, std::string> properties;

    sf::Sprite sprite;
};

struct Layer
{
    double opacity;
    std::vector<sf::Sprite> tiles;
};

class Level
{
public:
    Level();
    ~Level();

    bool loadFromFile(std::string filename);

    void draw(sf::RenderWindow &window);


    Object getObject(std::string name);

    std::vector<Object> getObjects(std::string name);

    std::vector<Object> getAllObjects() const;

    sf::Vector2i getTileSize() const;

    float getHeight() const;

    float getWidth() const;


private:
    float width, height, tileWidth, tileHeight;
    int firstTileID;
    sf::Rect<float> drawingBounds;
    sf::Texture tilesetImage;
    std::vector<Object> objects;
    std::vector<Layer> layers;
};
