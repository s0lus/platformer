#include "MenuScreen.h"


MenuScreen::MenuScreen()
{}


MenuScreen::~MenuScreen()
{}


int MenuScreen::run(sf::RenderWindow &window)
{
	sf::Event event;
	sf::Texture texture;
	sf::Sprite sprite;

	sf::View view(sf::FloatRect(0, 0, window.getSize().x, window.getSize().y));

	bool running = true;

	if (!texture.loadFromFile("res/img/background_1024x768.png"))
	{
		std::cerr << "Error loading fon" << std::endl;
		return (-1);
	}

	sprite.setTexture(texture);

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

	sf::FloatRect textRect;
	sf::Text startGame;
	sf::Text optionsGame;
	sf::Text aboutGame;
	sf::Text exitGame;

	startGame.setFont(font);
	startGame.setString("Start Game");
	textRect = startGame.getLocalBounds();
	startGame.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
	startGame.setPosition(sf::Vector2f(window.getSize().x / 2.0f, window.getSize().y / 2.0f - 50));

	optionsGame.setFont(font);
	optionsGame.setString("Options");
	textRect = optionsGame.getLocalBounds();
	optionsGame.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
	optionsGame.setPosition(sf::Vector2f(window.getSize().x / 2.0f, window.getSize().y / 2.0f));

	aboutGame.setFont(font);
	aboutGame.setString("About Game");
	textRect = aboutGame.getLocalBounds();
	aboutGame.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
	aboutGame.setPosition(sf::Vector2f(window.getSize().x / 2.0f, window.getSize().y / 2.0f + 50));

	exitGame.setFont(font);
	exitGame.setString("Exit");
	textRect = exitGame.getLocalBounds();
	exitGame.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
	exitGame.setPosition(sf::Vector2f(window.getSize().x / 2.0f, window.getSize().y / 2.0f + 100));


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
					case sf::Keyboard::Up:
					keyPressedSound.play();
					keyPressedSound.setVolume(50);
					menu--;
					break;

					case sf::Keyboard::Down:
					keyPressedSound.play();
					keyPressedSound.setVolume(50);
					menu++;
					break;

					case sf::Keyboard::Return:
					// Game Screen
					if (menu == 0)
					{
						return (1);
					}

					// Option Screen
					if (menu == 1)
					{
						std::cout << "Options btn pressed" << std::endl;
						return (3);
					}

					// About Screen
					if (menu == 2)
					{
						std::cout << "About btn pressed" << std::endl;
						return (2);
					}

					// Exit
					if (menu == 3)
					{
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

		if (menu > 3)
			menu = 3;

		//std::cout << "menu:" << menu << std::endl;

		if (menu == 0)
		{
			startGame.setColor(sf::Color::Red);
			optionsGame.setColor(sf::Color::White);
			aboutGame.setColor(sf::Color::White);
			exitGame.setColor(sf::Color::White);
		}

		if (menu == 1)
		{
			startGame.setColor(sf::Color::White);
			optionsGame.setColor(sf::Color::Red);
			aboutGame.setColor(sf::Color::White);
			exitGame.setColor(sf::Color::White);
		}

		if (menu == 2)
		{
			startGame.setColor(sf::Color::White);
			optionsGame.setColor(sf::Color::White);
			aboutGame.setColor(sf::Color::Red);
			exitGame.setColor(sf::Color::White);
		}

		if (menu == 3)
		{
			startGame.setColor(sf::Color::White);
			optionsGame.setColor(sf::Color::White);
			aboutGame.setColor(sf::Color::White);
			exitGame.setColor(sf::Color::Red);
		}

		window.setView(view);

		window.clear();

		window.draw(sprite);

		window.draw(startGame);
		window.draw(optionsGame);
		window.draw(aboutGame);
		window.draw(exitGame);

		window.display();
	}

	return (-1);
}