#include "GameScreen.h"

GameScreen::GameScreen()
{}

GameScreen::~GameScreen()
{}

int GameScreen::run(sf::RenderWindow &window)
{
    sf::View view(window.getView());
    view.zoom(0.50);
//    view.setViewport(sf::FloatRect(0.25f, 0.25, 0.5f, 0.5f));

    // Loading level
    Level lvl;
    lvl.loadFromFile("res/levels/level-1.tmx");


    // --------------------- Initialization main character --------------------- //

    // Loading main character
    sf::Texture spriteCharacter;
    spriteCharacter.loadFromFile("res/player/Hero_1.png");

    // Loading animation for main character
    AnimationManager animCharacter;
    animCharacter.loadFromXML("res/player/hero.xml", spriteCharacter);
    animCharacter.animationList["jump"].loop = 0;
    animCharacter.animationList["walk"].loop = 1;
    animCharacter.animationList["shoot"].loop = 0;

    // Loading animation bullet for main character
    AnimationManager bulletCharacter;
    bulletCharacter.loadFromXML("res/player/hero_bullet.xml", spriteCharacter);
    bulletCharacter.animationList["explode"].loop = 0;

    // ------------------------------------------------------------------------ //



    // --------------------- Initialization enemies --------------------- //


    // Loading enemy1
    sf::Texture enemy1;
    enemy1.loadFromFile("res/enemy/enemy1.png");

    // Loading animation for enemy1
    AnimationManager animEnemy1;
    animEnemy1.loadFromXML("res/enemy/enemy1.xml", enemy1);
    animEnemy1.animationList["move"].loop = 1;


    // Loading enemy1
    sf::Texture enemy2;
    enemy2.loadFromFile("res/enemy/enemy2.png");

    // Loading animation for enemy2
    AnimationManager animEnemy2;
    animEnemy2.loadFromXML("res/enemy/enemy2.xml", enemy2);
    animEnemy2.animationList["move"].loop = 1;


    // ------------------------------------------------------------------------ //



    // --------------------- Initialization game objects --------------------- //


    // Loading torch
    sf::Texture torchWithShadow;
    torchWithShadow.loadFromFile("res/objects/torch_and_shadow.png");

    // Loading animation for torch
    AnimationManager animTorchShadow;
    animTorchShadow.loadFromXML("res/objects/torch_and_shadow.xml", torchWithShadow);
    animTorchShadow.animationList["lighting"].loop = 1;


    sf::Texture torch;
    torch.loadFromFile("res/objects/torch.png");

    AnimationManager animTorch;
    animTorch.loadFromXML("res/objects/torch.xml", torch);
    animTorch.animationList["lighting"].loop = 1;

    // ------------------------------------------------------------------------ //


    std::list<Entity*> entities;
    std::list<Entity*>::iterator it;

    std::vector<Object> enemy1_ = lvl.getObjects("enemy1");
    for (int i = 0; i < enemy1_.size(); i++)
        entities.push_back(new Enemy(animEnemy1, lvl, enemy1_[i].rect.left, enemy1_[i].rect.top));

    std::vector<Object> enemy2_ = lvl.getObjects("enemy2");
    for (int i = 0; i < enemy2_.size(); i++)
        entities.push_back(new Enemy(animEnemy2, lvl, enemy2_[i].rect.left, enemy2_[i].rect.top));

    std::vector<Object> torchShadow_ = lvl.getObjects("torch_and_shadow");
    for (int i = 0; i < torchShadow_.size(); i++)
        entities.push_back(new Torch(animTorchShadow, lvl, torchShadow_[i].rect.left, torchShadow_[i].rect.top));

    std::vector<Object> torch_ = lvl.getObjects("torch");
    for (int i = 0; i < torch_.size(); i++)
        entities.push_back(new Torch(animTorch, lvl, torch_[i].rect.left, torch_[i].rect.top));

    Object pl = lvl.getObject("player");
    Player Hero(animCharacter, lvl, pl.rect.left, pl.rect.top);

    bool CanShoot = true;

    sf::Clock clock;
    sf::Clock fpsClock;


    float volume;
    MusicSettings musSet;
    musSet.getSoundSettings(volume);

    GameMusic arrowShoot;
    arrowShoot.loadMusic(volume, "res/music/arrow.ogg");

    while (window.isOpen()) {
        float time = clock.getElapsedTime().asMicroseconds();
        clock.restart();

        // Game speed
        time = time / gameSpeed;

        if (time > gameTick)
            time = gameTick;

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.key.code == sf::Keyboard::Escape) {
                return 0;
            }

            if (Hero.Health > 0) {
                if (event.type == sf::Event::KeyPressed) {
                    if ((event.key.code == sf::Keyboard::Space) && CanShoot) {
                        arrowShoot.playMusic(false);

                        entities.push_back(new Bullet(bulletCharacter, lvl, Hero.x + 18, Hero.y + 16, Hero.dir));

                        CanShoot = false;
                        Hero.key["Space"] = true;

                    }

                    if (event.key.code == sf::Keyboard::Right)
                        Hero.key["Right"] = true;

                    if (event.key.code == sf::Keyboard::Left)
                        Hero.key["Left"] = true;

                    if (event.key.code == sf::Keyboard::Up)
                        Hero.key["Up"] = true;

                    if (event.key.code == sf::Keyboard::Down)
                        Hero.key["Down"] = true;
                }
            }

            if (event.type == sf::Event::KeyReleased) {
                if (event.key.code == sf::Keyboard::Right)
                    Hero.key["Right"] = false;

                if (event.key.code == sf::Keyboard::Left)
                    Hero.key["Left"] = false;

                if (event.key.code == sf::Keyboard::Up)
                    Hero.key["Up"] = false;

                if (event.key.code == sf::Keyboard::Down)
                    Hero.key["Down"] = false;

                if (event.key.code == sf::Keyboard::Space) {
                    Hero.key["Space"] = false;
                    CanShoot = true;
                }
            }
        }

        for (it = entities.begin(); it != entities.end();) {
            Entity* b = *it;
            b->update(time);
            if (b->life == false) {
                it = entities.erase(it);
                delete b;
            } else it++;
        }

        Hero.update(time);

        if (Hero.Health > 0) {
            for (it = entities.begin(); it != entities.end(); it++) {
                if ((*it)->Name == "Enemy") {
                    Entity* enemy = *it;

                    if (enemy->Health <= 0)
                        continue;

                    if (Hero.getRect().intersects(enemy->getRect())) {
                        if (!Hero.hit) {
                            Hero.Health -= 50;
                            std::cout << Hero.Health << std::endl;
                            Hero.hit = true;

                            // GAME OVER
                            if (Hero.Health <= 0) {
                                return 5;
                            }

                            if (Hero.dir)
                                Hero.x += 10;
                            else
                                Hero.x -= 10;
                        }
                    }

                    for (std::list<Entity*>::iterator it2 = entities.begin(); it2 != entities.end(); it2++) {
                        Entity* bullet = *it2;
                        if (bullet->Name == "Bullet")
                            if (bullet->Health > 0)
                                if (bullet->getRect().intersects(enemy->getRect())) {
                                    bullet->Health = 0;
                                    enemy->Health -= 5;
                                }
                    }
                }
            }
        }

        // TODO: Extract magic numbers to const
        // TODO: Probably find a better way to cut off edges
        float tempX = Hero.x;
        float tempY = Hero.y;

        // Cut off left side
        if (Hero.x < 260) {
            tempX = 260;
        }

        // Cut off up side
        if (Hero.y < 260) {
            tempY = 260;
        }

        // Cut off right side
        if (Hero.x > 2945) {
            tempX = 2945;
        }

        // Cut off down side
        if (Hero.y > 450) {
            tempY = 450;
        }

        sf::Font fpsFont;
        if (!fpsFont.loadFromFile("res/font/numbers.ttf")) {
            std::cerr << "Error: can`t loading font - scoreFont.ttf" << std::endl;
            return (-1);
        }

        float fps = getFPS(fpsClock.restart());

        std::stringstream fpsStream;
        fpsStream << fps;

        sf::Text fpsText;
        fpsText.setFont(fpsFont);
        fpsText.setString(fpsStream.str());
        fpsText.setCharacterSize(24);
        fpsText.setFillColor(sf::Color::Red);

        fpsText.setPosition(tempX - 250, tempY - 180);

        view.setCenter(tempX, tempY);

        window.setView(view);

        window.clear();

        lvl.draw(window);

        for (it = entities.begin(); it != entities.end(); it++)
            (*it)->draw(window);

        Hero.draw(window);

        window.draw(fpsText);
        window.display();
    }

    return (-1);
}