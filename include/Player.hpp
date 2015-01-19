#ifndef PLAYER_HPP
# define PLAYER_HPP

# include "GameEntity.hpp"

class Player: protected GameEntity
{
private:
	int		_score;

public:
	Player();
	Player(Player const & rhs);
	~Player();
	Player &	operator=(Player const & rhs);

	int		getScore( void ) const;

	void	setScore(int score);

	void	addPoints(int score);

	bool	load(sf::Texture const & texture);
};

#endif
