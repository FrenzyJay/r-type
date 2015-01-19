#include "Player.hpp"

Player::Player():
GameEntity()
{}

Player::Player(Player const & rhs)
{
	*this = rhs;
}

Player::~Player()
{}

Player &	Player::operator=(Player const & rhs)
{
	this->_score = rhs.getScore();
	return *this;
}

int		getScore( void ) { return this->_score; }
void	setScore( void ) { this->_score = score; }

void	addPoints(int score)
{
	this->_score += score;
}
