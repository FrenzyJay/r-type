#ifndef GAME_ENTITY_HPP
# define GAME_ENTITY_HPP

# include <SFML/Graphics.hpp>

class GameEntity
{
private:
	sf::Sprite *	_sprite;

public:
	GameEntity();
	GameEntity(GameEntity const & rhs);
	~GameEntity();
	GameEntity &	operator=(GameEntity const & rhs);

	sf::Sprite *	getSprite( void );
	void			setSprite( void );

	void			update( void );
	void			draw(sf::RenderWindow & window);
};

#endif
