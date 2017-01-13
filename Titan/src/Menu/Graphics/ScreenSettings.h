#pragma once

#include <SFML/Graphics.hpp>

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