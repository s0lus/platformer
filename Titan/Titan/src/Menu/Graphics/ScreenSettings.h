#pragma once

#include <iostream>
#include <fstream>

class ScreenSettings
{
public:
	ScreenSettings();
	~ScreenSettings();

	bool getScreenSettigns();
	void setScreenSettings(bool screen);
};

