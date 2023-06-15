#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
class Player
{
private:
	
	sf::Sprite sprite;
	sf::Texture texture;

	float movementSpeed;
	float attackCoolDown;
	float attackCoolDownMax;

	int hp;
	int hpMax;
	//GUI
	
	//Private function
	void initVariables();
	void initTexture();
	void initSprite();

public:
	Player();
	virtual ~Player();

	//Accessor
	const sf::Vector2f& getPos() const;
	const sf::FloatRect getBounds() const;
	const int& getHp() const;
	const int& getHpMax() const;

	//Modifiers
	void setPosition(const sf::Vector2f pos);
	void setPosition(const float x, const float y);
	void setHp(const int hp);
	void lostHp(const int  value);

	//Function
	void move(const float dirX, const float dirY);

	const bool canAttack();
	void updateAttack();
	void update();
	void render(sf::RenderWindow& window);
};

