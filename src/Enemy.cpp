#include <iostream>
#include "Enemy.hpp"
#include "Projectile.hpp"
#include "EnemyProjectile.hpp"

Enemy::Enemy():
GameEntity()
{}

Enemy::Enemy(GameEngine & engine, int x, int y):
GameEntity()
{
	this->_width = 40;
	this->_height = 40;
	this->_speed = 400.f;
	this->_fireRate = 0.7f - (static_cast<float>(rand() % 200) / 1000);
	this->_lastShot = 1;
	this->_sprite = new sf::Sprite(engine.getTexture( PLAYER ));
	this->_sprite->rotate(180);
	this->_sprite->setPosition(x, y);
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
	this->_lastShot += elapsed * engine.getTimeRatio();
	if (p_sprite->getPosition().x > -50)
	{
		p_sprite->move(-this->_speed * elapsed * engine.getTimeRatio(), 0);
		if (this->_lastShot + elapsed > this->_fireRate)
		{
			engine.addEnemyProjectile(new EnemyProjectile(engine, this));
			this->_lastShot = 0;
		}
	}
	else
		engine.removeGameEntity(this);
}

