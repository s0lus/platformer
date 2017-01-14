#pragma once

#include <iostream>
#include <fstream>

class MusicSettings
{
public:
    MusicSettings();
    ~MusicSettings();

    void getSoundSettings(float &volume) const;
    void setSoundSettings(float &volume);
};