#include <iostream>
#include "Player.hpp"
#include "Projectile.hpp"
#include "Collision.hpp"

Player::Player():
GameEntity()
{}

Player::Player(GameEngine & engine):
GameEntity()
{
	this->_score = 0;
	this->_width = 40;
	this->_height = 40;
	this->_speed = 750.f;
	this->_fireRate = 0.2f;
	this->_lastShot = 1;
	this->_sprite = new sf::Sprite(engine.getTexture( PLAYER ));
	this->_sprite->setPosition(30, 280);
}

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

void	Player::update(GameEngine & engine, float elapsed)
{
	sf::Sprite *	p_sprite;

	p_sprite = engine.getPlayer()->getSprite();
	// input
	this->_lastShot += elapsed;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		if (p_sprite->getPosition().y > 5.f)
			p_sprite->move(0, -engine.getPlayer()->getSpeed() * elapsed * engine.getTimeRatio());
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		if (p_sprite->getPosition().y < engine.getHeight() - 40.f - 5.f)
			p_sprite->move(0, engine.getPlayer()->getSpeed() * elapsed * engine.getTimeRatio());
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		if (this->_lastShot + elapsed > this->_fireRate)
		{
			engine.addProjectile(new Projectile(engine));
			this->_lastShot = 0;
		}
	}
	// collide
	for (std::list<GameEntity *>::iterator i = engine.getGameEntities().begin(); i != engine.getGameEntities().end(); ++i)
	{
		if (Collision::PixelPerfectTest(*(this->_sprite),*((*i)->getSprite())))
		{
			engine.removeGameEntity(*i);
		}
	}
}
