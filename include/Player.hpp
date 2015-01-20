#ifndef PLAYER_HPP
# define PLAYER_HPP

# include "GameEntity.hpp"

class GameEngine;

class Player : public GameEntity
{
private:
	int		_score;

public:
	Player();
	Player(GameEngine & engine);
	Player(Player const & rhs);
	virtual ~Player();
	Player &	operator=(Player const & rhs);

	int		getScore( void ) const;

	void	setScore(int score);

	void	addPoints(int score);

	virtual void	update(GameEngine & engine, float elapsed);
};

#endif
