#include "Level.h"

Level::Level()
{}

Level::~Level()
{}

int Object::getPropertyInt(std::string name)
{
    return atoi(properties[name].c_str());
}

float Object::getPropertyFloat(std::string name)
{
    return (float) strtod(properties[name].c_str(), NULL);
}

std::string Object::getPropertyString(std::string name)
{
    return properties[name];
}

bool Level::loadFromFile(std::string filename)
{
    tinyxml2::XMLDocument levelFile;

    if (!levelFile.LoadFile(filename.c_str())) {
        std::cout << "Loading level \"" << filename << "\" failed." << std::endl;
        return false;
    }

    tinyxml2::XMLElement *map;
    map = levelFile.FirstChildElement("map");

    width = atoi(map->Attribute("width"));
    height = atoi(map->Attribute("height"));
    tileWidth = atoi(map->Attribute("tilewidth"));
    tileHeight = atoi(map->Attribute("tileheight"));

    tinyxml2::XMLElement *tilesetElement;
    tilesetElement = map->FirstChildElement("tileset");
    firstTileID = atoi(tilesetElement->Attribute("firstgid"));

    tinyxml2::XMLElement *image;
    image = tilesetElement->FirstChildElement("image");
    std::string imagepath = image->Attribute("source");

    sf::Image img;
    if (!img.loadFromFile(imagepath)) {
        std::cout << "Failed to load tile sheet." << std::endl;
        return false;
    }


    img.createMaskFromColor(sf::Color::White);
    tilesetImage.loadFromImage(img);
    tilesetImage.setSmooth(false);

    float columns = tilesetImage.getSize().x / tileWidth;
    float rows = tilesetImage.getSize().y / tileHeight;

    std::vector<sf::Rect<int>> subRects;

    for (size_t y = 0; y < rows; y++)
        for (size_t x = 0; x < columns; x++) {
            sf::Rect<int> rect;

            rect.top = y * tileHeight;
            rect.height = tileHeight;
            rect.left = x * tileWidth;
            rect.width = tileWidth;

            subRects.push_back(rect);
        }

    tinyxml2::XMLElement *layerElement;
    layerElement = map->FirstChildElement("layer");
    while (layerElement) {
        Layer layer;

        if (layerElement->Attribute("opacity") != NULL) {
            double opacity = strtod(layerElement->Attribute("opacity"), NULL);
            layer.opacity = 255 * opacity;
        } else {
            layer.opacity = 255;
        }

        tinyxml2::XMLElement *layerDataElement;
        layerDataElement = layerElement->FirstChildElement("data");

        if (layerDataElement == NULL) {
            std::cout << "Bad map. No layer information found." << std::endl;
        }

        tinyxml2::XMLElement *tileElement;
        tileElement = layerDataElement->FirstChildElement("tile");

        if (tileElement == NULL) {
            std::cout << "Bad map. No tile information found." << std::endl;
            return false;
        }

        float x = 0;
        int y = 0;

        while (tileElement) {
            int tileGID = atoi(tileElement->Attribute("gid"));
            int subRectToUse = tileGID - firstTileID;

            if (subRectToUse >= 0) {
                sf::Sprite sprite;
                sprite.setTexture(tilesetImage);
                sprite.setTextureRect(subRects[subRectToUse]);
                sprite.setPosition(x * tileWidth, y * tileHeight);
                sprite.setColor(sf::Color(255, 255, 255, layer.opacity));

                layer.tiles.push_back(sprite);
            }

            tileElement = tileElement->NextSiblingElement("tile");

            x++;
            if (x >= width) {
                x = 0;
                y++;
                if (y >= height)
                    y = 0;
            }
        }

        layers.push_back(layer);

        layerElement = layerElement->NextSiblingElement("layer");
    }
    
    tinyxml2::XMLElement *objectGroupElement;

    if (map->FirstChildElement("objectgroup") != NULL) {
        objectGroupElement = map->FirstChildElement("objectgroup");
        while (objectGroupElement) {
            tinyxml2::XMLElement *objectElement;
            objectElement = objectGroupElement->FirstChildElement("object");

            while (objectElement) {
                std::string objectType;
                if (objectElement->Attribute("type") != NULL) {
                    objectType = objectElement->Attribute("type");
                }

                std::string objectName;
                if (objectElement->Attribute("name") != NULL) {
                    objectName = objectElement->Attribute("name");
                }

                int x = atoi(objectElement->Attribute("x"));
                int y = atoi(objectElement->Attribute("y"));

                int width, height;

                sf::Sprite sprite;
                sprite.setTexture(tilesetImage);
                sprite.setTextureRect(sf::Rect<int>(0, 0, 0, 0));
                sprite.setPosition(x, y);

                if (objectElement->Attribute("width") != NULL) {
                    width = atoi(objectElement->Attribute("width"));
                    height = atoi(objectElement->Attribute("height"));
                } else {
                    width = subRects[atoi(objectElement->Attribute("gid")) - firstTileID].width;
                    height = subRects[atoi(objectElement->Attribute("gid")) - firstTileID].height;
                    sprite.setTextureRect(subRects[atoi(objectElement->Attribute("gid")) - firstTileID]);
                }

                Object object;
                object.name = objectName;
                object.type = objectType;
                object.sprite = sprite;

                sf::Rect<float> objectRect;
                objectRect.top = y;
                objectRect.left = x;
                objectRect.height = height;
                objectRect.width = width;
                object.rect = objectRect;

                tinyxml2::XMLElement *properties;
                properties = objectElement->FirstChildElement("properties");
                if (properties != NULL) {
                    tinyxml2::XMLElement *prop;
                    prop = properties->FirstChildElement("property");
                    if (prop != NULL) {
                        while (prop) {
                            std::string propertyName = prop->Attribute("name");
                            std::string propertyValue = prop->Attribute("value");

                            object.properties[propertyName] = propertyValue;

                            prop = prop->NextSiblingElement("property");
                        }
                    }
                }

                objects.push_back(object);

                objectElement = objectElement->NextSiblingElement("object");
            }
            objectGroupElement = objectGroupElement->NextSiblingElement("objectgroup");
        }
    } else {
        std::cout << "No object layers found..." << std::endl;
    }

    return true;
}

Object Level::getObject(std::string name)
{
    for (size_t i = 0; i < objects.size(); i++)
        if (objects[i].name == name) {
            return objects[i];
        }
}

std::vector<Object> Level::getObjects(std::string name)
{
    std::vector<Object> vec;
    for (size_t i = 0; i < objects.size(); i++)
        if (objects[i].name == name) {
            vec.push_back(objects[i]);
        }

    return vec;
}

std::vector<Object> Level::getAllObjects() const
{
    return objects;
};

sf::Vector2i Level::getTileSize() const
{
    return sf::Vector2i(tileWidth, tileHeight);
}

void Level::draw(sf::RenderWindow &window)
{
    for (size_t layer = 0; layer < layers.size(); layer++) {
        for (size_t tile = 0; tile < layers[layer].tiles.size(); tile++) {
            window.draw(layers[layer].tiles[tile]);
        }
    }
}

float Level::getHeight() const
{
    return height;
}

float Level::getWidth() const
{
    return width;
}