#pragma once
#include <map>
#include <string>
#include <sstream>
#include "Player.h"
#include "Bullet.h"
#include "Enemy.h"
class Game
{
private:
	sf::RenderWindow* window;

	//Resources
	std::map<std::string, sf::Texture*> textures;
	std::vector<Bullet*> bullets;

	//GUI
	sf::Font font;
	sf::Text pointText;
	
	sf::Text gameOverText;

	sf::Text restartText;
	//World
	sf::Texture woldBackgroundTex;
	sf::Sprite worldBackground;
	//Player
	Player* player;
	
	//Player GUI
	sf::RectangleShape playerHpBar;
	sf::RectangleShape playerHpBarBack;

	//System
	unsigned points;


	//Enemy
	std::vector <Enemy*> enemies;
	float spawnTimer;
	float spawnTimerMax;

	
	//private function
	void initWindow();
	void initPlayer();
	void initTexture();
	void initGUI();
	void initWorld();
	void initSystems();

	void initEnemies();
public:
	Game();
	virtual ~Game();
	//Functions
	void run();
	void restart();
	
	void updatePollEvents();
	void updateInput();
	void updateGUI();
	void updateWorld();
	void updateCollision();
	void updateBullets();
	void updateEnemies();
	void updateCombat();
	void update();

	void renderWorld();
	void renderGUI();
	void render();
};

