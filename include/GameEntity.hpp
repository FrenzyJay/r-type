#ifndef GAME_ENTITY_HPP
# define GAME_ENTITY_HPP

# include <SFML/Graphics.hpp>
# include "GameEngine.hpp"

class GameEngine;

class GameEntity
{
protected:
	sf::Sprite *	_sprite;
	int				_life;
	int				_maxlife;
	float			_speed;
	int				_width;
	int				_height;

public:
	GameEntity();
	GameEntity(sf::Sprite * sprite);
	GameEntity(GameEntity const & rhs);
	virtual ~GameEntity();
	GameEntity &	operator=(GameEntity const & rhs);

	sf::Sprite *	getSprite( void ) const;
	int				getLife( void ) const;
	int				getMaxLife( void ) const;
	float			getSpeed( void ) const;

	void			setSprite(sf::Sprite * sprite);
	void			setLife(int life);
	void			setMaxLife(int max);
	void			setSpeed(float speed);

	void			hit(int damage);

	virtual void			update(GameEngine & engine, float elapsed) = 0;
	void			draw(GameEngine & engine);
};

#endif
