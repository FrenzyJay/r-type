#include <iostream>
#include "Collision.hpp"
#include "EnemyProjectile.hpp"

EnemyProjectile::EnemyProjectile():
GameEntity()
{}

EnemyProjectile::EnemyProjectile(GameEngine & engine, Enemy * enemy):
GameEntity()
{
	this->_damage = 20;
	this->_width = 15;
	this->_height = 15;
	this->_speed = 800.f;
	this->_sprite = new sf::Sprite(engine.getTexture( ENEMY_PROJECTILE ));
	this->_sprite->setPosition(enemy->getSprite()->getPosition().x - 30, enemy->getSprite()->getPosition().y - 25 );
}

EnemyProjectile::EnemyProjectile(EnemyProjectile const & rhs):
GameEntity()
{
	*this = rhs;
}

EnemyProjectile::~EnemyProjectile()
{}

EnemyProjectile &	EnemyProjectile::operator=(EnemyProjectile const & rhs)
{
	static_cast<void>(rhs);
	return *this;
}

int				EnemyProjectile::getDamage( void ) const { return this->_damage; }
void			EnemyProjectile::setDamage(int damage) { this->_damage = damage; }

void			EnemyProjectile::update(GameEngine & engine, float elapsed)
{
	this->_sprite->move(-this->_speed * elapsed * engine.getTimeRatio(), 0.f);
	if (this->_sprite->getPosition().x > engine.getWidth())
		engine.removeGameEntity(this);
	else
	{
		if (Collision::PixelPerfectTest(*(this->_sprite), *(engine.getPlayer()->getSprite())))
		{
			engine.removeGameEntity(this);
		}
	}
}
