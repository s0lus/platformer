#include "Music/MusicSettings.h"
#include "MusicScreen.h"


MusicScreen::MusicScreen()
{}

MusicScreen::~MusicScreen()
{}

int MusicScreen::run(sf::RenderWindow &window)
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

	sf::Text musicVolume;
	sf::FloatRect textRect;

	musicVolume.setFont(font);
	musicVolume.setString("Music Volume");
	musicVolume.setColor(sf::Color::Black);
	textRect = musicVolume.getLocalBounds();
	musicVolume.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
	musicVolume.setPosition(sf::Vector2f(window.getSize().x / 2.0f, window.getSize().y / 2.0f - 150));

	sf::Font font1;
	if (!font1.loadFromFile("res/font/musicSet.ttf"))
	{
		std::cerr << "Error loading font" << std::endl;
		return (-1);
	}

	sf::Text selectedVolume;
	selectedVolume.setFont(font1);
	selectedVolume.setColor(sf::Color::Red);
	textRect = selectedVolume.getLocalBounds();
	selectedVolume.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
	selectedVolume.setPosition(sf::Vector2f(window.getSize().x / 2.0f - 20, window.getSize().y / 2.0f - 55));


	float volume;
	float selection;

	MusicSettings musSet;
	musSet.getSoundSettings(volume);
	selection = volume;

	std::stringstream selectionStream;

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
						return (3);
						break;

					case sf::Keyboard::Right:
						if (selection < 100)
						{
							selection += 5;
						}
						else
						{
							selection = 100;
						}
						break;

					case sf::Keyboard::Left:
						if (selection > 0)
						{
							selection -= 5;
						}
						break;

					case sf::Keyboard::Return:
							musSet.setSoundSettings(selection);
							return (3);
					default:
						break;
				}
			}
		}

		// Updating music volume
		selectedVolume.setString(selectionStream.str());
		selectionStream.str("");
		selectionStream << selection;

		window.clear();

		window.draw(sprite);
		window.draw(musicVolume);
		window.draw(selectedVolume);

		window.display();
	}

	return (-1);
}