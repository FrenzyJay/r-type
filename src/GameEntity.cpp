#include "GameEntity.hpp"

GameEntity::GameEntity():
_sprite(NULL)
{}

GameEntity::GameEntity(sf::Sprite const * sprite):
_sprite(sprite)
{}

GameEntity::GameEntity(GameEntity const & rhs)
{}

GameEntity::~GameEntity()
{
	delete this->_sprite;
}

GameEntity &	GameEntity::operator=(GameEntity const & rhs)
{
	*this = rhs;
}

sf::Sprite *	getSprite( void ) { return this->_sprite; }
int				getLife( void ) { return this->_life; }
int				getMaxLife( void ) { return this->_maxlife; }
float			getSpeed( void ) { return this->_speed; }

void			setSprite(sf::Sprite * sprite) { this->_sprite = sprite; }
void			setLife(int life) { this->_life = life; }
void			setMaxLife(int max) { this->_maxlife = max; }
void			setSpeed(float speed) { this->_speed = speed; }

void			hit(int damage)
{
	if (this->_life >= 0)
		this->_life -= damage;
}

void			update( void )
{

}

void			draw(sf::RenderWindow & window)
{
	(void)window;
}
