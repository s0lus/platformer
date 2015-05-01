#include "AboutScreen.h"


AboutScreen::AboutScreen()
{}


AboutScreen::~AboutScreen()
{}

int AboutScreen::Run(sf::RenderWindow &window)
{
	sf::Texture texture;
	if (!texture.loadFromFile("res/img/background_1280x1024.png"))
	{
		std::cerr << "Error loading fon" << std::endl;
		return (-1);
	}

	sf::Sprite sprite;
	sprite.setTexture(texture);

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