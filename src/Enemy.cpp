#include <iostream>
#include "Enemy.hpp"
#include "Projectile.hpp"

Enemy::Enemy():
GameEntity()
{}

Enemy::Enemy(GameEngine & engine):
GameEntity()
{
	this->_width = 40;
	this->_height = 40;
	this->_speed = 400.f;
	this->_fireRate = 0.5f;
	this->_lastShot = 0;
	this->_sprite = new sf::Sprite(engine.getTexture( PLAYER ));
	this->_sprite->rotate(180);
	this->_sprite->setPosition(1000, 280);
}

Enemy::Enemy(Enemy const & rhs):
GameEntity()
{
	*this = rhs;
}

Enemy::~Enemy()
{}

Enemy &	Enemy::operator=(Enemy const & rhs)
{
	static_cast<void>(rhs);
	return *this;
}

void	Enemy::update(GameEngine & engine, float elapsed)
{
	sf::Sprite *	p_sprite;

	p_sprite = this->_sprite;
	this->_lastShot += elapsed;
	if (p_sprite->getPosition().x > -50)
		p_sprite->move(-this->_speed * elapsed, 0);
	else
		engine.removeGameEntity(this);
}

