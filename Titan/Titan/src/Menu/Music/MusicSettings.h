#pragma once

#include <iostream>
#include <fstream>

class MusicSettings
{
public:
	MusicSettings();
	~MusicSettings();

	void ReadSoundSettings(float &volume);
	void WriteSoundSettings(float &volume);
};