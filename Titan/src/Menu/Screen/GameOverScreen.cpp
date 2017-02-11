#include "GameOverScreen.h"

GameOverScreen::GameOverScreen()
{}

GameOverScreen::~GameOverScreen()
{}

int GameOverScreen::run(sf::RenderWindow &window)
{
    sf::View view(sf::FloatRect(0, 0, window.getSize().x, window.getSize().y));

    sf::VideoMode mode = sf::VideoMode::getDesktopMode();

    sf::Texture texture;
    sf::Sprite sprite;

    isFullScreen = scrSet.getScreenSettings();

    if (isFullScreen) {
        if (mode.width == 1680 && mode.height == 1050) {
            if (!texture.loadFromFile("res/img/game_over_1680x1050.png")) {
                std::cerr << "Error: can`t loading image - game_over_1680x1050.png" << std::endl;
                return (-1);
            }
            sprite.setTexture(texture);
        } else if (mode.width == 1280 && mode.height == 1024) {
            if (!texture.loadFromFile("res/img/game_over_1280x1024.png")) {
                std::cerr << "Error: can`t loading image - game_over_1280x1024.png" << std::endl;
                return (-1);
            }
            sprite.setTexture(texture);
        } else if (mode.width == 1366 && mode.height == 768) {
            if (!texture.loadFromFile("res/img/game_over_1366x768.png")) {
                std::cerr << "Error: can`t loading image - game_over_1366x768.png" << std::endl;
                return (-1);
            }
            sprite.setTexture(texture);
        }
    } else {
        if (!texture.loadFromFile("res/img/game_over_1024x768.png")) {
            std::cerr << "Error: can`t loading image - game_over_1024x768.png" << std::endl;
            return (-1);
        }
        sprite.setTexture(texture);
    }


    sf::Font font;
    if (!font.loadFromFile("res/font/menuFont.ttf")) {
        std::cerr << "Error loading font: menuFont.ttf" << std::endl;
    }

    sf::FloatRect textRect;
    sf::Text gameOverText;

    gameOverText.setFont(font);
    gameOverText.setString("GAME OVER");
    textRect = gameOverText.getLocalBounds();
    gameOverText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
    gameOverText.setPosition(sf::Vector2f(window.getSize().x / 2.0f, window.getSize().y / 2.0f));


    bool running = true;
    sf::Event event;
    while (running) {
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                return (-1);
            }

            // Back to main menu
            if (event.key.code == sf::Keyboard::Return) {
                return 0;
            }

        }

        window.clear();

        window.setView(view);
        window.draw(sprite);
        window.draw(gameOverText);

        window.display();
    }
}
