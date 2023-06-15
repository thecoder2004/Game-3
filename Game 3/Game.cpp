#include "Game.h"
//Private function
void Game::initWindow()
{
	this->window = new sf::RenderWindow(sf::VideoMode(800.f, 600.f), "Game 3", sf::Style::Close|sf::Style::Titlebar);
	this->window->setFramerateLimit(144);
	this->window->setVerticalSyncEnabled(false);
}

void Game::initPlayer()
{
	this->player = new Player();
}

void Game::initTexture()
{
	this->textures["BULLET"] = new sf::Texture();
	this->textures["BULLET"]->loadFromFile("Textures/bullet.png");
}

void Game::initGUI()
{
	//Load font
	if (!this->font.loadFromFile("Fonts/Dosis-Light.ttf"))
	{
		std::cout << "Failed to load font" << std::endl;
	};
	//Init point text
	this->pointText.setFont(this->font);
	this->pointText.setCharacterSize(36);
	this->pointText.setFillColor(sf::Color::White);
	this->pointText.setString("Test");

	this->gameOverText.setFont(this->font);
	this->gameOverText.setCharacterSize(72);
	this->gameOverText.setFillColor(sf::Color::Red);
	this->gameOverText.setString("Game Over!");
	this->gameOverText.setPosition
	(this->window->getSize().x/2.f - this->gameOverText.getGlobalBounds().width/2.f,
	 this->window->getSize().y/2.f - this->gameOverText.getGlobalBounds().height/2.f);

	this->restartText.setFont(this->font);
	this->restartText.setCharacterSize(60);
	this->restartText.setFillColor(sf::Color::Yellow);
	this->restartText.setString("Restart");
	this->restartText.setPosition
	(this->window->getSize().x / 2.f - this->restartText.getGlobalBounds().width / 2.f,
	 this->window->getSize().y / 2.f + this->restartText.getGlobalBounds().height );

	//Init player GUI
	this->playerHpBar.setSize(sf::Vector2f(this->player->getBounds().width, 10.f));
	this->playerHpBar.setFillColor(sf::Color::Green);
	this->playerHpBar.setPosition(sf::Vector2f(this->player->getBounds().left, this->player->getBounds().top));

	this->playerHpBarBack.setSize(sf::Vector2f(this->player->getBounds().width, 10.f));
	this->playerHpBarBack.setFillColor(sf::Color(sf::Color::Red));
	this->playerHpBarBack.setPosition(sf::Vector2f(this->player->getBounds().left, this->player->getBounds().top));
}

void Game::initWorld()
{
	if (!this->woldBackgroundTex.loadFromFile("Textures/background1.jpg"))
	{
		std::cout << "Failed to load texture file!" << std::endl;
	}
	this->worldBackground.setTexture(this->woldBackgroundTex);
}

void Game::initSystems()
{
	this->points = 0;
}

void Game::initEnemies()
{
	this->spawnTimerMax = 20.f;
	this->spawnTimer = this->spawnTimerMax;
}

Game::Game()
{
	this->initWindow();
	this->initPlayer();
	this->initTexture();
	this->initGUI();
	this->initWorld();
	this->initSystems();
	this->initEnemies();
}

Game::~Game()
{
	delete this->window;
	delete this->player;

	//Delete textures
	for (auto& i : this->textures)
	{
		delete i.second;
	}

	//Delete bullets
	for (auto* i : this->bullets)
	{
		delete i;
	}
	for (int i = 0; i < this->enemies.size(); ++i)
	{
		delete this->enemies[i];
	}
}

//Functions
void Game::run()
{
	while (this->window->isOpen())
	{
		this->updatePollEvents();
		if (this->player->getHp() > 0)
		{
			this->update();
			
			
		}
		else
		{
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				sf::Vector2i mouse = sf::Mouse::getPosition(*this->window);
				if (this->restartText.getGlobalBounds().contains(mouse.x, mouse.y))
				{
					this->restart();
				}
			}
			
			if (sf::Event::MouseMoved)
			{
				sf::Vector2i mouse = sf::Mouse::getPosition(*this->window);
				if (this->restartText.getGlobalBounds().contains(mouse.x, mouse.y))
				{
					this->restartText.setFillColor(sf::Color::Magenta);
				}
				else
				{
					this->restartText.setFillColor(sf::Color::Yellow);
				}
			}


		}
		this->render();
	}
}

void Game::restart()
{
	this->points = 0;
	this->bullets.clear();
	this->enemies.clear();
	this->player->setHp(this->player->getHpMax());
}

void Game::updatePollEvents()
{
	sf::Event e;
	while (this->window->pollEvent(e))
	{
		if (e.type == sf::Event::Closed)
		{
			this->window->close();
		}
		if (e.KeyPressed && e.key.code == sf::Keyboard::Escape)
		{
			this->window->close();
		}
	}
}

void Game::updateInput()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		this->player->move(-1.f, 0.f);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		this->player->move(1.f, 0.f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		this->player->move(0.f, -1.f);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		this->player->move(0.f, 1.f);
	}
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->player->canAttack())
	{
		this->bullets.push_back(
			new Bullet(this->textures["BULLET"],
			this->player->getPos().x + this->player->getBounds().width /2.3023f ,
			this->player->getPos().y,
			0.f, 
			-1.f, 
			5.f));
	}
}

void Game::updateGUI()
{
	std::stringstream ss;
	ss << "Points: " << this->points;
	this->pointText.setString(ss.str());
	
	//Update player GUI
	float hpPercent = static_cast<float>(this->player->getHp()) / this->player->getHpMax();
	this->playerHpBar.setSize(sf::Vector2f(this->player->getBounds().width * hpPercent, this->playerHpBar.getSize().y));
	this->playerHpBar.setPosition(sf::Vector2f(this->player->getBounds().left, this->player->getBounds().top - 20.f));
	this->playerHpBarBack.setPosition(sf::Vector2f(this->player->getBounds().left, this->player->getBounds().top - 20.f));
}

void Game::updateWorld()
{

}

void Game::updateCollision()
{
	//Left
	if (this->player->getBounds().left < 0.f)
	{
		this->player->setPosition(0.f, this->player->getBounds().top);
	}
	//Right
	else if (this->player->getBounds().left + this->player->getBounds().width >= this->window->getSize().x)
	{
		this->player->setPosition(this->window->getSize().x - this->player->getBounds().width, this->player->getBounds().top);
	}
	//Top
	if (this->player->getBounds().top < 0.f)
	{
		this->player->setPosition(this->player->getBounds().left, 0.f);
	}
	//Bottom
	else if (this->player->getBounds().top + this->player->getBounds().height >= this->window->getSize().y)
	{
		this->player->setPosition(this->player->getBounds().left, this->window->getSize().y - this->player->getBounds().height);
	}
}

void Game::updateBullets()
{
	for (int i = 0; i < this->bullets.size(); ++i)
	{
		this->bullets[i]->update();
		if (this->bullets[i]->getBounds().top + this->bullets[i]->getBounds().height < 0)
		{
			delete this->bullets[i];
			this->bullets.erase(this->bullets.begin() + i);
		}
	}
}

void Game::updateEnemies()
{
	//Spawning
	this->spawnTimer += 0.5f;
	if (this->spawnTimer >= this->spawnTimerMax)
	{
		this->enemies.push_back(new Enemy(rand() % (this->window->getSize().x - 40), -100.f));
		this->spawnTimer = 0.f;
	}
	//Updating
	for (int i = 0; i < this->enemies.size(); ++i)
	{
		this->enemies[i]->update();

		//Culling the screen (bottom of the screen)
		if (this->enemies[i]->getBounds().top > this->window->getSize().y)
		{
			delete this->enemies[i];
			this->enemies.erase(this->enemies.begin() + i);
		}

		//Collision with the player
		else if (this->enemies[i]->getBounds().intersects(this->player->getBounds()))
		{
			this->player->lostHp(this->enemies[i]->getPoints());
			delete this->enemies[i];
			this->enemies.erase(this->enemies.begin() + i);
		}
	}
}

void Game::updateCombat()
{
	for (int i = 0; i < this->enemies.size(); ++i)
	{
		bool enemy_deleted = false;
		for (int k = 0; k < this->bullets.size() && !enemy_deleted; ++k)
		{
			if (this->enemies[i]->getBounds().intersects(this->bullets[k]->getBounds()))
			{
				this->points += this->enemies[i]->getPoints();
				delete this->enemies[i];
				this->enemies.erase(this->enemies.begin() + i);

				delete this->bullets[k];
				this->bullets.erase(this->bullets.begin() + k);

				enemy_deleted = true;
			}
		}
	}
}


void Game::update()
{
	this->updateInput();

	this->player->update();

	this->updateCollision();

	this->updateBullets();

	this->updateEnemies();

	this->updateCombat();

	this->updateGUI();
	
	this->updateWorld();
}

void Game::renderWorld()
{
	this->window->draw(this->worldBackground);
}

void Game::renderGUI()
{
	this->window->draw(this->pointText);
	this->window->draw(this->playerHpBarBack);
	this->window->draw(this->playerHpBar);
}

void Game::render()
{
	this->window->clear();
	//Draw world
	this->renderWorld();

	//Draw all the stuffs
	this->player->render(*this->window);
	for (int i = 0; i < this->bullets.size(); ++i)
	{
		this->bullets[i]->render(*this->window);
	}

	for (int i = 0; i < this->enemies.size(); ++i)
	{
		this->enemies[i]->render(this->window);
	}
	this->renderGUI();

	//Game over screen
	if (this->player->getHp() <= 0)
	{
		this->window->draw(this->gameOverText);
		this->window->draw(this->restartText);
	}

	this->window->display();
}
