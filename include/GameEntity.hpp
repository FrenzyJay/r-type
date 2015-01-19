#ifndef GAME_ENTITY_HPP
# define GAME_ENTITY_HPP

# include <SFML/Graphics.hpp>

class GameEntity
{
private:
	sf::Sprite *	_sprite;
	int				_life;
	int				_maxlife;
	float			_speed;

public:
	GameEntity();
	GameEntity(GameEntity const & rhs);
	~GameEntity();
	GameEntity &	operator=(GameEntity const & rhs);

	sf::Sprite *	getSprite( void );
	int				getLife( void );
	int				getMaxLife( void );
	float			getSpeed( void );

	void			setSprite( void );
	void			setLife(int life);
	void			setMaxLife(int max);
	void			setSpeed(float speed);

	void			hit(int damage);

	void			update( void );
	void			draw(sf::RenderWindow & window);
};

#endif
