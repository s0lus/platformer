#include "AboutScreen.h"


AboutScreen::AboutScreen()
{}


AboutScreen::~AboutScreen()
{}

int AboutScreen::run(sf::RenderWindow &window)
{
	sf::VideoMode mode = sf::VideoMode::getDesktopMode();

	sf::Texture texture;
	sf::Sprite sprite;

	isFullScreen = scrSet.getScreenSettigns();

	if (isFullScreen)
	{
		if (mode.width == 1680 && mode.height == 1050)
		{
			if (!texture.loadFromFile("res/img/background_1680x1050.png"))
			{
				std::cerr << "Error: can`t loading image - background_1680x1050.png" << std::endl;
				return (-1);
			}
			sprite.setTexture(texture);
		}
		else if (mode.width == 1280 && mode.height == 1024)
		{
			if (!texture.loadFromFile("res/img/background_1280x1204.png"))
			{
				std::cerr << "Error: can`t loading image - background_1280x1204.png" << std::endl;
				return (-1);
			}
			sprite.setTexture(texture);
		}
		else if (mode.width == 1366 && mode.height == 768)
		{
			if (!texture.loadFromFile("res/img/background_1366x768.png"))
			{
				std::cerr << "Error: can`t loading image - background_1366x768.png" << std::endl;
				return (-1);
			}
			sprite.setTexture(texture);
		}
	}
	else
	{
		if (!texture.loadFromFile("res/img/background_1024x768.png"))
		{
			std::cerr << "Error: can`t loading image - background_1024x768.png" << std::endl;
			return (-1);
		}
		sprite.setTexture(texture);
	}

	sf::Font font;
	if (!font.loadFromFile("res/font/menuFont.ttf"))
	{
		std::cerr << "Error loading font" << std::endl;
		return (-1);
	}

	sf::Event event;
	bool running = true;

	while (running)
	{
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				return (-1);
			}

			if (event.type == sf::Event::KeyPressed)
			{
				switch (event.key.code)
				{
					case sf::Keyboard::Escape:
						return (0);
						break;
				
					default:
						break;
				}
			}
		}
	
		window.clear();

		window.draw(sprite);

		window.display();
	}

	return (-1);
}