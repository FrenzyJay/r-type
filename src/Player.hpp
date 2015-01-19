#ifndef PLAYER_HPP
# define PLAYER_HPP

class Player: public GameEntity
{
private:
	int		_score;

public:
	Player();
	Player(Player const & rhs);
	~Player();
	Player &	operator=(Player const & rhs);

	int		getScore( void );
	void	setScore(int score);

	void	addPoints(int score);
};

#endif
