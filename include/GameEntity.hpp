#ifndef GAME_ENTITY_HPP
# define GAME_ENTITY_HPP

# include <SFML/Graphics.hpp>

class GameEntity
{
protected:
	sf::Sprite *	_sprite;
	int				_life;
	int				_maxlife;
	float			_speed;

public:
	GameEntity();
	GameEntity(sf::Sprite * sprite);
	GameEntity(GameEntity const & rhs);
	~GameEntity();
	GameEntity &	operator=(GameEntity const & rhs);

	sf::Sprite *	getSprite( void ) const;
	int				getLife( void ) const;
	int				getMaxLife( void ) const;
	float			getSpeed( void ) const;

	void			setSprite( sf::Sprite * sprite );
	void			setLife(int life);
	void			setMaxLife(int max);
	void			setSpeed(float speed);

	void			hit(int damage);

	void			update( void );
	void			draw(sf::RenderWindow & window);
};

#endif
