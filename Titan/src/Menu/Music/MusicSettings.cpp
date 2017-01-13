#include "MusicSettings.h"


MusicSettings::MusicSettings()
{}


MusicSettings::~MusicSettings()
{}


void MusicSettings::getSoundSettings(float &volume) const

{
	std::ifstream file;
	file.open("settings/musicsettings.txt", std::ios::in);

	if (!file)
	{
		std::cerr << "Error open file: musicsettings.txt" << std::endl;
	}

	file >> volume;

	file.close();
}


void MusicSettings::setSoundSettings(float &volume)
{
	std::ofstream file;
	file.open("settings/musicsettings.txt", std::ios::out);

	if (!file)
	{
		std::cerr << "Error open file: musicsettings.txt" << std::endl;
	}

	file << volume;

	file.close();
}