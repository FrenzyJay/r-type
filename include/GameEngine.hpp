#ifndef GAME_ENGINE_HPP
# define GAME_ENGINE_HPP

# include "GameEntity.hpp"

class GameEngine
{
public:
	GameEngine();
	GameEngine(GameEngine const & rhs);
	~GameEngine();
	GameEngine &	operator=(GameEngine const & rhs);

	std::list < GameEntity *> &		getGameEntities( void );

	void							addGameEntity( GameEntity const * entity);
	void							removeGameEntity( GameEntity const * entity );

private:
	std::list < GameEntity * >	_gameEntities;
};

#endif
