#include "GameEngine.hpp"

GameEngine::GameEngine()
{}

GameEngine::GameEngine(GameEngine const & rhs)
{
	*this = rhs;
}

GameEngine::~GameEngine()
{}

GameEngine &	GameEngine::operator=(GameEngine const & rhs)
{
	this->_gameEntities = rhs.getGameEntities();
	return *this;
}

void			GameEngine::addGameEntity(GameEntity * entity)
{
	this->_gameEntities.push_back(entity);
}

void			GameEngine::removeGameEntity(GameEntity * entity)
{
	for (std::list<GameEntity *>::iterator i = this->_gameEntities.begin(); i != this->_gameEntities.end(); ++i)
	{
		if (*i == entity)
		{
			delete *i;
			i = this->_gameEntities.erase(i);
		}
	}
}

std::list < GameEntity * >		GameEngine::getGameEntities( void ) const { return this->_gameEntities; }

