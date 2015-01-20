#include "Player.hpp"

Player::Player():
GameEntity()
{}

Player::Player(GameEngine & engine):
GameEntity()
{
	this->_score = 0;
	this->_width = 40;
	this->_height = 40;
	this->_sprite = new sf::Sprite(engine.getTexture( PLAYER ));
	this->_sprite->setPosition(50, 430);
}

Player::Player(Player const & rhs):
GameEntity()
{
	*this = rhs;
}

Player::~Player()
{
	delete this->_sprite;
}

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

void	Player::update(GameEngine & engine, float elapsed)
{
	(void)engine;
	(void)elapsed;
}
