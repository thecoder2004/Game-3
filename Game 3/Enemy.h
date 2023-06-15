#ifndef ENEMY_H
#define ENEMY_H

#include <SFML/Graphics.hpp>

class Enemy
{
private:
	unsigned pointCount;
	sf::CircleShape shape;
	int type;
	int hp;
	float speed;
	int hpMax;
	int damage;
	int points;

	void initVariables();
	void initShape();
public:
	Enemy(float pos_x, float pos_y);
	virtual ~Enemy();
	//Accessor
	const sf::FloatRect getBounds() const;
	const int& getPoints() const;
	const int& getDamage() const;
	//Function
	void update();
	void render(sf::RenderWindow* window);
};
#endif // Enemy.h!