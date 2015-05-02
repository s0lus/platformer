#include "GameScreen.h"


GameScreen::GameScreen()
{}


GameScreen::~GameScreen()
{}

int GameScreen::Run(sf::RenderWindow &window)
{

	//sf::View view(sf::FloatRect(0, 0, 400, 250));
	sf::View view(window.getView());
	view.zoom(0.50);

	sf::Vector2u screen;

	screen = window.getSize();

	Level lvl;
	lvl.loadFromFile("res/levels/level_1.tmx");

	sf::Texture hero_sprite;
	hero_sprite.loadFromFile("res/player/Hero_1.png");

	AnimationManager anim;
	anim.loadFromXML("res/player/hero.xml", hero_sprite);
	anim.animList["jump"].loop = 0;
	anim.animList["walk"].loop = 1;
	anim.animList["shoot"].loop = 0;

	//Анимация врагов
	sf::Texture Enemy_1;
	Enemy_1.loadFromFile("res/enemy/enemy_2.png");

	AnimationManager anim_e;
	anim_e.loadFromXML("res/enemy/enemy_2.xml", Enemy_1);
	anim_e.animList["move"].loop = 1;


	AnimationManager anim2;  //Пули героя       
	anim2.loadFromXML("res/player/hero_bullet.xml", hero_sprite);
	anim2.animList["explode"].loop = 0;


	std::list<Entity*>  entities;
	std::list<Entity*>::iterator it;

	std::vector<Object> e = lvl.getObjects("enemy");
	for (int i = 0; i < e.size(); i++)
		entities.push_back(new Enemy(anim_e, lvl, e[i].rect.left, e[i].rect.top));

	Object pl = lvl.getObject("player");
	Player Hero(anim, lvl, pl.rect.left, pl.rect.top);

	sf::Clock clock;

	//Переменные, задающие камеру
	float offsetX = 0, offsetY = 0;

	//Переменная, может ли сделать еще выстрел персонаж
	bool CanShoot = true;

	/////////////////// основной цикл  /////////////////////
	while (window.isOpen())
	{
		float time = clock.getElapsedTime().asMicroseconds();
		clock.restart();

		time = time / gameSpeed;  // здесь регулируем скорость игры

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
						if (!Hero.dir)
							entities.push_back(new Bullet(anim2, lvl, Hero.x + 18, Hero.y + 16, Hero.dir));
						else
							entities.push_back(new Bullet(anim2, lvl, Hero.x + 18, Hero.y + 16, Hero.dir));

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

		//Обновляем состояние всех сущностей, если сущность "убита", удаляем ее из массива
		for (it = entities.begin(); it != entities.end();)
		{
			Entity *b = *it;
			b->update(time);
			if (b->life == false)
			{
				it = entities.erase(it); delete b;
			}
			else it++;
		}

		Hero.update(time);


		//Обрабатываем взаимодействие сущностей друг с другом
		//Только если здоровье персонажа больше 0
		if (Hero.Health>0)
		for (it = entities.begin(); it != entities.end(); it++)
		{
			//1. враги
			if ((*it)->Name == "Enemy")
			{
				Entity *enemy = *it;

				if (enemy->Health <= 0) continue;

				//Если персонаж наткнулся на врага
				if (Hero.getRect().intersects(enemy->getRect()))
				if (!Hero.hit)
				{
					Hero.Health -= 5;
					Hero.hit = true;

					if (Hero.dir)
						Hero.x += 10;
					else
						Hero.x -= 10;
				}

				//Обрабатываем пули врага и персонажа
				for (std::list<Entity*>::iterator it2 = entities.begin(); it2 != entities.end(); it2++)
				{
					Entity *bullet = *it2;
					if (bullet->Name == "Bullet")
					if (bullet->Health>0)
					if (bullet->getRect().intersects(enemy->getRect()))
					{
						bullet->Health = 0;
						enemy->Health -= 5;
					}
				}
			}

		}

		//view.setCenter(Hero.x, Mario.y);


		/*if ((Mario.x > screen.x/2) && ((lvl.getW() - Mario.x) > screen.x/2))
		offsetX = Mario.x;

		if ((lvl.getH() - Mario.y) > screen.y/2)

		offsetY = Mario.y;*/

		view.setCenter(Hero.x, Hero.y);

		window.setView(view);

		window.clear();

		lvl.draw(window);

		for (it = entities.begin(); it != entities.end(); it++)
			(*it)->draw(window);

		Hero.draw(window);

		window.display();
	}

	return (-1);
}
