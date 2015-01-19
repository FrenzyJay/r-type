#include "GameEntity.hpp"

GameEntity::GameEntity():
_sprite(NULL)
{}

GameEntity::GameEntity(sf::Sprite * sprite):
_sprite(sprite)
{}

GameEntity::GameEntity(GameEntity const & rhs)
{
	*this = rhs;
}

GameEntity::~GameEntity()
{
	delete this->_sprite;
}

GameEntity &	GameEntity::operator=(GameEntity const & rhs)
{
	this->_sprite = rhs.getSprite();
	this->_life = rhs.getLife();
	this->_maxlife = rhs.getMaxLife();
	this->_speed = rhs.getSpeed();
	return *this;
}

sf::Sprite *	GameEntity::getSprite( void ) const { return this->_sprite; }
int				GameEntity::getLife( void ) const { return this->_life; }
int				GameEntity::getMaxLife( void ) const { return this->_maxlife; }
float			GameEntity::getSpeed( void ) const { return this->_speed; }

void			GameEntity::setSprite(sf::Sprite * sprite) { this->_sprite = sprite; }
void			GameEntity::setLife(int life) { this->_life = life; }
void			GameEntity::setMaxLife(int max) { this->_maxlife = max; }
void			GameEntity::setSpeed(float speed) { this->_speed = speed; }

void			GameEntity::hit(int damage)
{
	if (this->_life >= 0)
		this->_life -= damage;
}

void			GameEntity::update( void )
{

}

void			GameEntity::draw(sf::RenderWindow & window)
{
	(void)window;
}
