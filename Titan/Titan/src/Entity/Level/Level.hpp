#pragma once

#include <SFML/Graphics.hpp>

#include <string>
#include <vector>
#include <map>
#include <iostream>

#include <tinyxml.h>

struct Object
{
    int GetPropertyInt(std::string name);
	double GetPropertyFloat(std::string name);
    std::string GetPropertyString(std::string name);

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

    bool LoadFromFile(std::string filename);
    Object GetObject(std::string name);
    std::vector<Object> GetObjects(std::string name);
	std::vector<Object> GetAllObjects();
    void Draw(sf::RenderWindow &window);
	sf::Vector2i GetTileSize();
	float getHeight();
	float getWidth();


private:
    float width, height, tileWidth, tileHeight;
    int firstTileID;
    sf::Rect<float> drawingBounds;
    sf::Texture tilesetImage;
    std::vector<Object> objects;
    std::vector<Layer> layers;
};
