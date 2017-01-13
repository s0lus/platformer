#include "GameScreen.h"


GameScreen::GameScreen()
{}


GameScreen::~GameScreen()
{}

int GameScreen::run(sf::RenderWindow &window)
{
	sf::View view(window.getView());
	view.zoom(0.50);

	// Loading level
	Level lvl;
	lvl.loadFromFile("res/levels/level_1.tmx");


	// --------------------- Initialization main character --------------------- //

	// Loading main character
	sf::Texture spriteCharacter;
	spriteCharacter.loadFromFile("res/player/Hero_1.png");

	// Loading animation for main character
	AnimationManager animCharacter;
	animCharacter.loadFromXML("res/player/hero.xml", spriteCharacter);
	animCharacter.animList["jump"].loop = 0;
	animCharacter.animList["walk"].loop = 1;
	animCharacter.animList["shoot"].loop = 0;

	// Loading animation bullet for main character
	AnimationManager bulletCharacter;
	bulletCharacter.loadFromXML("res/player/hero_bullet.xml", spriteCharacter);
	bulletCharacter.animList["explode"].loop = 0;

	// ------------------------------------------------------------------------ //



	// --------------------- Initialization enemies --------------------- //


	// Loading enemy1
	sf::Texture enemy1;
	enemy1.loadFromFile("res/enemy/enemy1.png");

	// Loading animation for enemy1
	AnimationManager animEnemy1;
	animEnemy1.loadFromXML("res/enemy/enemy1.xml", enemy1);
	animEnemy1.animList["move"].loop = 1;


	// Loading enemy1
	sf::Texture enemy2;
	enemy2.loadFromFile("res/enemy/enemy2.png");

	// Loading animation for enemy2
	AnimationManager animEnemy2;
	animEnemy2.loadFromXML("res/enemy/enemy2.xml", enemy2);
	animEnemy2.animList["move"].loop = 1;


	// ------------------------------------------------------------------------ //



	// --------------------- Initialization game objects --------------------- //


	// Loading torch
	sf::Texture torchWithShadow;
	torchWithShadow.loadFromFile("res/objects/torch_and_shadow.png");

	// Loading animation for torch
	AnimationManager animTorchShadow;
	animTorchShadow.loadFromXML("res/objects/torch_and_shadow.xml", torchWithShadow);
	animTorchShadow.animList["lighting"].loop = 1;


	sf::Texture torch;
	torch.loadFromFile("res/objects/torch.png");

	AnimationManager animTorch;
	animTorch.loadFromXML("res/objects/torch.xml", torch);
	animTorch.animList["lighting"].loop = 1;

	// ------------------------------------------------------------------------ //


	std::list<Entity*>  entities;
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


	// Переменная, может ли сделать еще выстрел персонаж
	bool CanShoot = true;

	sf::Clock clock;
	sf::Clock fpsClock;


	float volume;
	MusicSettings musSet;
	musSet.getSoundSettings(volume);

	InGameMusic arrowShoot;
	arrowShoot.loadMusic(volume, "res/music/arrow.ogg");

	while (window.isOpen())
	{
		float time = clock.getElapsedTime().asMicroseconds();
		clock.restart();

		// Game speed
		time = time / gameSpeed;

		if (time > gameTick)
			time = gameTick;

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			if (event.key.code == sf::Keyboard::Escape)
			{
				return 0;
			}

			if (Hero.Health > 0)
			{
				if (event.type == sf::Event::KeyPressed)
				{
					if ((event.key.code == sf::Keyboard::Space) && CanShoot)
					{
						arrowShoot.playMusic(false);

						if (!Hero.dir)
							entities.push_back(new Bullet(bulletCharacter, lvl, Hero.x + 18, Hero.y + 16, Hero.dir));
						else
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

			if (event.type == sf::Event::KeyReleased)
			{
				if (event.key.code == sf::Keyboard::Right)
					Hero.key["Right"] = false;

				if (event.key.code == sf::Keyboard::Left)
					Hero.key["Left"] = false;

				if (event.key.code == sf::Keyboard::Up)
					Hero.key["Up"] = false;

				if (event.key.code == sf::Keyboard::Down)
					Hero.key["Down"] = false;

				if (event.key.code == sf::Keyboard::Space)
				{
					Hero.key["Space"] = false;
					CanShoot = true;
				}
			}
		}

		// Обновляем состояние всех сущностей, если сущность "убита", удаляем ее из массива
		for (it = entities.begin(); it != entities.end();)
		{
			Entity *b = *it;
			b->update(time);
			if (b->life == false)
			{
				it = entities.erase(it);
				delete b;
			}
			else it++;
		}

		Hero.update(time);


		//Обрабатываем взаимодействие сущностей друг с другом
		//Только если здоровье персонажа больше 0
		if (Hero.Health > 0)
		{
			for (it = entities.begin(); it != entities.end(); it++)
			{
				//1. враги
				if ((*it)->Name == "Enemy")
				{
					Entity *enemy = *it;

					if (enemy->Health <= 0)
						continue;

					//Если персонаж наткнулся на врага
					if (Hero.getRect().intersects(enemy->getRect()))
					{
						if (!Hero.hit)
						{
							Hero.Health -= 50;
							std::cout << Hero.Health << std::endl;
							Hero.hit = true;

							// GAME OVER
							if (Hero.Health <= 0)
							{
								return 5;
							}

							if (Hero.dir)
								Hero.x += 10;
							else
								Hero.x -= 10;
						}
					}

					//Обрабатываем пули врага и персонажа
					for (std::list<Entity*>::iterator it2 = entities.begin(); it2 != entities.end(); it2++)
					{
						Entity *bullet = *it2;
						if (bullet->Name == "Bullet")
							if (bullet->Health > 0)
								if (bullet->getRect().intersects(enemy->getRect()))
								{
									bullet->Health = 0;
									enemy->Health -= 5;
								}
					}
				}
			}
		}

		view.setCenter(Hero.x, Hero.y);

		window.setView(view);

		window.clear();

		std::cout << "fps: " << getFPS(fpsClock.restart()) << std::endl;

		lvl.draw(window);

		for (it = entities.begin(); it != entities.end(); it++)
			(*it)->draw(window);

		Hero.draw(window);

		window.display();
	}

	return (-1);
}