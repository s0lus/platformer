#pragma once

#include <iostream>
#include <fstream>

class MusicSettings
{
public:
	MusicSettings();
	~MusicSettings();

	void readSoundSettings(float &volume);
	void writeSoundSettings(float &volume);
};