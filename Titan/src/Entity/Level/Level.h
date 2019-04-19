#pragma once

#include <SFML/Graphics.hpp>

#include <string>
#include <vector>
#include <map>
#include <iostream>

#include "tinyxml2.h"

struct Object
{
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

private:
    float width, height, tileWidth, tileHeight;
    int firstTileID;
    sf::Texture tilesetImage;
    std::vector<Object> objects;
    std::vector<Layer> layers;
};
