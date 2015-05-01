#include "ScreenSettings.h"


ScreenSettings::ScreenSettings()
{}


ScreenSettings::~ScreenSettings()
{}


bool ScreenSettings::getScreenSettigns()
{
	std::ifstream file;
	file.open("settings/screensettings.txt");

	if (!file)
	{
		std::cerr << "Error open file: screensettings.txt" << std::endl;
	}

	bool temp;
	file >> temp;

	file.close();

	return temp;
}

// 1 - FullScreen;  0 - Default Mode (1280x1024)
void ScreenSettings::setScreenSettings(bool screen)
{
	std::ofstream file;
	file.open("settings/screensettings.txt", std::ios::out);

	file << screen;

	file.close();
}