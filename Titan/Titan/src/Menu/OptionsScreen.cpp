#include "OptionsScreen.h"


OptionsScreen::OptionsScreen()
{}


OptionsScreen::~OptionsScreen()
{}


int OptionsScreen::run(sf::RenderWindow &window)
{
	sf::Event event;
	sf::Texture texture;
	sf::Sprite sprite;

	sf::Font font;

	sf::Music keyPressedSound;

	bool running = true;

	int menu = 0;

	if (!texture.loadFromFile("res/img/background_1024x768.png"))
	{
		std::cerr << "Error loading fon" << std::endl;
		return (-1);
	}

	sprite.setTexture(texture);

	if (!font.loadFromFile("res/font/menuFont.ttf"))
	{
		std::cerr << "Error loading font" << std::endl;
		return (-1);
	}

	if (!keyPressedSound.openFromFile("res/music/keyPressed.ogg"))
	{
		std::cerr << "Error loading music" << std::endl;
		return (-1);
	}

	sf::Text graphics;
	sf::Text music;
	sf::FloatRect textRect;

	graphics.setFont(font);
	graphics.setString("Graphics");
	textRect = graphics.getLocalBounds();
	graphics.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
	graphics.setPosition(sf::Vector2f(window.getSize().x / 2.0f, window.getSize().y / 2.0f));

	music.setFont(font);
	music.setString("Music");
	textRect = music.getLocalBounds();
	music.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
	music.setPosition(sf::Vector2f(window.getSize().x / 2.0f, window.getSize().y / 2.0f + 50));

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
						return 0;
						break;

					case sf::Keyboard::Down:
						keyPressedSound.play();
						keyPressedSound.setVolume(50);
						menu++; 
						break;

					case sf::Keyboard::Up:
						keyPressedSound.play();
						keyPressedSound.setVolume(50);
						menu--;
						break;

					case sf::Keyboard::Return:
						// Graphics settings screen
						if (menu == 0)
						{
							return (4);
						}

						// Music settings screen
						if (menu == 1)
						{
							return (5);
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

		if (menu == 0)
		{
			graphics.setColor(sf::Color::Red);
			music.setColor(sf::Color::White);
		}

		if (menu == 1)
		{
			graphics.setColor(sf::Color::White);
			music.setColor(sf::Color::Red);
		}

		window.clear();

		window.draw(sprite);

		window.draw(graphics);
		window.draw(music);

		window.display();
	}

	return (-1);
}