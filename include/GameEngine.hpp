#ifndef GAME_ENGINE_HPP
# define GAME_ENGINE_HPP

# include <list>
# include "GameEntity.hpp"

class GameEngine
{
public:
	GameEngine();
	GameEngine(GameEngine const & rhs);
	~GameEngine();
	GameEngine &	operator=(GameEngine const & rhs);

	std::list < GameEntity *>		getGameEntities( void ) const;

	void							addGameEntity( GameEntity * entity);
	void							removeGameEntity( GameEntity * entity );

private:
	std::list < GameEntity * >	_gameEntities;
};

#endif
