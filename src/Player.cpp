#include "Player.hpp"

Player::Player():
GameEntity()
{}

Player::Player(Player const & rhs):
GameEntity()
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

int		Player::getScore( void ) const { return this->_score; }
void	Player::setScore( int score ) { this->_score = score; }

void	Player::addPoints(int score)
{
	this->_score += score;
}

bool	Player::load(sf::Texture const & texture)
{
	this->_sprite = new sf::Sprite(texture);
	return true;
}
