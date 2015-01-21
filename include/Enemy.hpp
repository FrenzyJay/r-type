#ifndef ENEMY_HPP
# define ENEMY_HPP

# include "GameEntity.hpp"

class GameEngine;

class Enemy : public GameEntity
{
private:
	float	_fireRate;
	float	_lastShot;

public:
	Enemy();
	Enemy(GameEngine & engine);
	Enemy(Enemy const & rhs);
	virtual ~Enemy();
	Enemy &		operator=(Enemy const & rhs);

	virtual void	update(GameEngine & engine, float elapsed);
};

#endif
