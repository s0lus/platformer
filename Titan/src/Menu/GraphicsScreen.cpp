#include "GraphicsScreen.h"


GraphicsScreen::GraphicsScreen()
{}


GraphicsScreen::~GraphicsScreen()
{}


int GraphicsScreen::run(sf::RenderWindow &window)
{
	sf::VideoMode mode = sf::VideoMode::getDesktopMode();

	sf::Texture texture;
	sf::Sprite sprite;

	isFullScreen = scrSet.getScreenSettigns();

	if (isFullScreen)
	{
		if (mode.width == 1680 && mode.height == 1050)
		{
			if (!texture.loadFromFile("res/img/setScrMode_1680x1050.png"))
			{
				std::cerr << "Error: can`t loading image - setScrMode_1680x1050.png" << std::endl;
				return (-1);
			}
			sprite.setTexture(texture);
		}
		else if (mode.width == 1280 && mode.height == 1024)
		{
			if (!texture.loadFromFile("res/img/setScrMode_1280x1024.png"))
			{
				std::cerr << "Error: can`t loading image - setScrMode_1280x1024.png" << std::endl;
				return (-1);
			}
			sprite.setTexture(texture);
		}
		else if (mode.width == 1366 && mode.height == 768)
		{
			if (!texture.loadFromFile("res/img/setScrMode_1366x768.png"))
			{
				std::cerr << "Error: can`t loading image - setScrMode_1366x768.png" << std::endl;
				return (-1);
			}
			sprite.setTexture(texture);
		}
	}
	else
	{
		if (!texture.loadFromFile("res/img/setScrMode_1024x768.png"))
		{
			std::cerr << "Error: can`t loading image - setScrMode_1024x768.png" << std::endl;
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

	sf::Music keyPressedSound;
	if (!keyPressedSound.openFromFile("res/music/keyPressed.ogg"))
	{
		std::cerr << "Error loading music" << std::endl;
		return (-1);
	}

	sf::Music okSound;
	if (!okSound.openFromFile("res/music/okSound.ogg"))
	{
		std::cerr << "Error loading music" << std::endl;
		return (-1);
	}

	sf::Text fullScreen;
	sf::FloatRect textRect;

	fullScreen.setFont(font);
	fullScreen.setString("FullScreen");
	fullScreen.setColor(sf::Color::Black);
	textRect = fullScreen.getLocalBounds();
	fullScreen.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
	fullScreen.setPosition(sf::Vector2f(window.getSize().x / 2.0f, window.getSize().y / 2.0f - 150));

	sf::Text on, off;

	on.setFont(font);
	on.setString("On");
	textRect = on.getLocalBounds();
	on.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
	on.setPosition(sf::Vector2f(window.getSize().x / 2.0f, window.getSize().y / 2.0f - 35));

	off.setFont(font);
	off.setString("Off");
	textRect = off.getLocalBounds();
	off.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
	off.setPosition(sf::Vector2f(window.getSize().x / 2.0f, window.getSize().y / 2.0f - 35));

	sf::Text help;

	help.setFont(font);
	help.setString("You must restart the game");
	help.setColor(sf::Color::Black);
	textRect = help.getLocalBounds();
	help.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
	help.setPosition(sf::Vector2f(window.getSize().x / 2.0f, window.getSize().y / 2.0f + 250));


	sf::Event event;
	bool running = true;
	int menu = 0;

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
					return (2);
					break;

					case sf::Keyboard::Right:
					keyPressedSound.play();
					keyPressedSound.setVolume(50);
					menu++;
					break;

					case sf::Keyboard::Left:
					keyPressedSound.play();
					keyPressedSound.setVolume(50);
					menu--;
					break;

					case sf::Keyboard::Return:
					if (menu == 0)
					{
						okSound.play();
						okSound.setVolume(75);
						scrSet.setScreenSettings(true);
						// restart game for change resolution
						return (-1);
					}
					else
					{
						okSound.play();
						okSound.setVolume(75);
						scrSet.setScreenSettings(false);
						// restart game for change resolution
						return (-1);
					}
					break;

					default:
					break;
				}
			}
		}

		if (menu < 0)
			menu = 0;
		if (menu > 1)
			menu = 1;

		//std::cout << "menu: " << menu << std::endl;

		window.clear();

		window.draw(sprite);
		window.draw(fullScreen);
		window.draw(help);

		if (menu == 0)
		{
			on.setColor(sf::Color::Red);
			window.draw(on);
		}

		if (menu == 1)
		{
			off.setColor(sf::Color::Red);
			window.draw(off);
		}

		window.display();
	}

	return (-1);
}