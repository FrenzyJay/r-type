#include <iostream>
#include "Collision.hpp"
#include "Projectile.hpp"

Projectile::Projectile():
GameEntity()
{}

Projectile::Projectile(GameEngine & engine):
GameEntity()
{
	this->_damage = 20;
	this->_width = 15;
	this->_height = 15;
	this->_speed = 400.f;
	this->_sprite = new sf::Sprite(engine.getTexture( PROJECTILE ));
	this->_sprite->setPosition(engine.getPlayer()->getSprite()->getPosition().x + 10, engine.getPlayer()->getSprite()->getPosition().y + 10 );
}

Projectile::Projectile(Projectile const & rhs):
GameEntity()
{
	*this = rhs;
}

Projectile::~Projectile()
{}

Projectile &	Projectile::operator=(Projectile const & rhs)
{
	(void)rhs;
	return *this;
}

int				Projectile::getDamage( void ) const { return this->_damage; }
void			Projectile::setDamage(int damage) { this->_damage = damage; }

void			Projectile::update(GameEngine & engine, float elapsed)
{
	this->_sprite->move(this->_speed * elapsed, 0.f);
	if (this->_sprite->getPosition().x > engine.getWidth())
		engine.removeProjectile(this);
	else
	{
		// collide with enemies
		for (std::list<GameEntity *>::iterator i = engine.getGameEntities().begin(); i != engine.getGameEntities().end(); )
		{
			if (Collision::PixelPerfectTest(*(this->_sprite), *((*i)->getSprite())))
			{
				// crap too, call the hit member function of gameentity but gameneity does not store gameengine so f*ck off
				engine.removeGameEntity(*i);
				// this is crap, soon it will be the gun fire member function that will be called
				engine.removeProjectile(this);
				break;
			}
			else
				++i;
		}
	}
}
