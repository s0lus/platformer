#include "OptionsScreen.h"

OptionsScreen::OptionsScreen()
{}

OptionsScreen::~OptionsScreen()
{}

int OptionsScreen::run(sf::RenderWindow &window)
{
    sf::VideoMode mode = sf::VideoMode::getDesktopMode();

    sf::Texture texture;
    sf::Sprite sprite;

    isFullScreen = scrSet.getScreenSettings();

    if (isFullScreen) {
        if (mode.width == 1680 && mode.height == 1050) {
            if (!texture.loadFromFile("res/img/background_1680x1050.png")) {
                std::cerr << "Error: can`t loading image - background_1680x1050.png" << std::endl;
                return (-1);
            }
            sprite.setTexture(texture);
        } else if (mode.width == 1280 && mode.height == 1024) {
            if (!texture.loadFromFile("res/img/background_1280x1204.png")) {
                std::cerr << "Error: can`t loading image - background_1280x1204.png" << std::endl;
                return (-1);
            }
            sprite.setTexture(texture);
        } else if (mode.width == 1366 && mode.height == 768) {
            if (!texture.loadFromFile("res/img/background_1366x768.png")) {
                std::cerr << "Error: can`t loading image - background_1366x768.png" << std::endl;
                return (-1);
            }
            sprite.setTexture(texture);
        }
    } else {
        if (!texture.loadFromFile("res/img/background_1024x768.png")) {
            std::cerr << "Error: can`t loading image - background_1024x768.png" << std::endl;
            return (-1);
        }
        sprite.setTexture(texture);
    }


    sf::Font font;
    if (!font.loadFromFile("res/font/menuFont.ttf")) {
        std::cerr << "Error loading font" << std::endl;
        return (-1);
    }

    sf::Music keyPressedSound;
    if (!keyPressedSound.openFromFile("res/music/keyPressed.ogg")) {
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


    sf::Event event;
    int menu = 0;

    while (true) {
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                return (-1);
            }

            if (event.type == sf::Event::KeyPressed) {
                switch (event.key.code) {
                    case sf::Keyboard::Escape:
                        return 0;

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
                        if (menu == 0) {
                            return (3);
                        }

                        // Music settings screen
                        if (menu == 1) {
                            return (4);
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

        if (menu == 0) {
            graphics.setFillColor(sf::Color::Red);
            music.setFillColor(sf::Color::White);
        }

        if (menu == 1) {
            graphics.setFillColor(sf::Color::White);
            music.setFillColor(sf::Color::Red);
        }

        window.clear();

        window.draw(sprite);

        window.draw(graphics);
        window.draw(music);

        window.display();
    }
}