#pragma once

#include <iostream>
#include <fstream>

class ScreenSettings
{
public:
	ScreenSettings();
	~ScreenSettings();

	bool getScreenSettigns() const;
	void setScreenSettings(bool screen);
};