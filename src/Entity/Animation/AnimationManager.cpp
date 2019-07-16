#include "AnimationManager.h"

AnimationManager::AnimationManager()
{}

AnimationManager::~AnimationManager()
{
    animationList.clear();
}


void AnimationManager::loadFromXML(std::string fileName, sf::Texture &t)
{
    tinyxml2::XMLDocument animFile;

    animFile.LoadFile(fileName.c_str());

    tinyxml2::XMLElement* head;
    head = animFile.FirstChildElement("sprites");

    tinyxml2::XMLElement* animElement;
    animElement = head->FirstChildElement("animation");
    while (animElement) {
        Animation animation;
        currentAnimation = animElement->Attribute("title");
        float delay = atoi(animElement->Attribute("delay"));
        animation.speed = 1.f / delay;
        animation.sprite.setTexture(t);

        tinyxml2::XMLElement* cut;
        cut = animElement->FirstChildElement("cut");
        while (cut) {
            int x = atoi(cut->Attribute("x"));
            int y = atoi(cut->Attribute("y"));
            int w = atoi(cut->Attribute("w"));
            int h = atoi(cut->Attribute("h"));

            animation.frames.push_back(sf::IntRect(x, y, w, h));
            animation.frames_flip.push_back(sf::IntRect(x + w, y, -w, h));
            cut = cut->NextSiblingElement("cut");
        }

        animation.sprite.setOrigin(0, animation.frames[0].height);

        animationList[currentAnimation] = animation;
        animElement = animElement->NextSiblingElement("animation");
    }
}

void AnimationManager::set(sf::String name)
{
    currentAnimation = name;
    animationList[currentAnimation].flip = 0;
}

void AnimationManager::draw(sf::RenderWindow &window, float x, float y)
{
    animationList[currentAnimation].sprite.setPosition(x, y);
    window.draw(animationList[currentAnimation].sprite);
}

void AnimationManager::flip(bool b)
{
    animationList[currentAnimation].flip = b;
}

void AnimationManager::tick(float time)
{
    animationList[currentAnimation].tick(time);
}

void AnimationManager::pause()
{
    animationList[currentAnimation].isPlaying = false;
}

void AnimationManager::play()
{
    animationList[currentAnimation].isPlaying = true;
}

void AnimationManager::play(sf::String name)
{
    animationList[name].isPlaying = true;
}

bool AnimationManager::isPlaying()
{
    return animationList[currentAnimation].isPlaying;
}

float AnimationManager::getHeight()
{
    return animationList[currentAnimation].frames[0].height;
}

float AnimationManager::getWidth()
{
    return animationList[currentAnimation].frames[0].width;
}