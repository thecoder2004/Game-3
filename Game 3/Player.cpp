#include "Player.h"

void Player::initVariables()
{
	this->attackCoolDownMax = 10.0;
	this->attackCoolDown = this->attackCoolDownMax;
	this->movementSpeed = 3.f;

	this->hpMax = 100;
	this->hp = this->hpMax;
}

void Player::initTexture()
{
	if (!this->texture.loadFromFile("Textures/ship.png"))
	{
		std::cout << "ERROR::PLAYER::INITTEXTURE::Could not load texture file." << std::endl;
	};
}

void Player::initSprite()
{
	this->sprite.setTexture(this->texture);
	this->sprite.scale(0.1f, 0.1f);
}

Player::Player()
{
	this->initVariables();
	this->initTexture();
	this->initSprite();
}

Player::~Player()
{
}

const sf::Vector2f& Player::getPos() const
{
	return this->sprite.getPosition();
}

const sf::FloatRect Player::getBounds() const
{
	return this->sprite.getGlobalBounds();
}

const int& Player::getHp() const
{
	return this->hp;
}

const int& Player::getHpMax() const
{
	return this->hpMax;
}

void Player::setPosition(const sf::Vector2f pos)
{
	this->sprite.setPosition(pos);
}

void Player::setPosition(const float x, const float y)
{
	this->sprite.setPosition(x, y);
}

void Player::setHp(const int hp)
{
	this->hp = hp;
}

void Player::lostHp(const int value)
{
	this->hp -= value;
	if (this->hp < 0)
		this->hp = 0;
}

void Player::move(const float dirX, const float dirY)
{
	this->sprite.move(this->movementSpeed * dirX, this->movementSpeed * dirY);
}

const bool Player::canAttack()
{
	if (this->attackCoolDown >= this->attackCoolDownMax)
	{
		this->attackCoolDown = 0.f;
		return true;
	}
	return false;
}

void Player::updateAttack()
{
	if (this->attackCoolDown < this->attackCoolDownMax)
		this->attackCoolDown += 0.5f;
	
}

void Player::update()
{
	this->updateAttack();
}

void Player::render(sf::RenderWindow& window)
{
	window.draw(this->sprite);
}
