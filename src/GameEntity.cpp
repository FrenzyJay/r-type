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
void			setSprite(sf::Sprite * sprite) { this->_sprite = sprite; }

void			update( void )
{

}

void			draw(sf::RenderWindow & window)
{
	(void)window;
}
