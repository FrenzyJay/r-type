#include <iostream>
#include "GameEngine.hpp"
#include "Player.hpp"
#include "Enemy.hpp"

GameEngine::GameEngine()
{}

GameEngine::GameEngine(int width, int height)
{
	this->_window = new sf::RenderWindow(sf::VideoMode(width, height), "PEW PEW PEW");
	this->_width = width;
	this->_height = height;
	this->_firstLaunch = true;
	this->_pause = false;
	Collision::CreateTextureAndBitmask(this->_textures[0], "assets/player.png");
	Collision::CreateTextureAndBitmask(this->_textures[1], "assets/laser.png");
	Collision::CreateTextureAndBitmask(this->_textures[2], "assets/evil-pony.png");
	Collision::CreateTextureAndBitmask(this->_textures[3], "assets/enemy-laser.png");
	
	this->_timeRatio = 1.0f;

	this->_player = new Player(*this);
}

GameEngine::GameEngine(GameEngine const & rhs)
{
	*this = rhs;
}

GameEngine::~GameEngine()
{
	delete this->_window;
	for (std::list<GameEntity *>::iterator i = this->_gameEntities.begin(); i != this->_gameEntities.end(); ++i)
		delete *i;
	for (std::list<GameEntity *>::iterator i = this->_projectiles.begin(); i != this->_projectiles.end(); ++i)
		delete *i;
}

GameEngine &		GameEngine::operator=(GameEngine const & rhs)
{
	static_cast<void>(rhs);
	return *this;
}

sf::RenderWindow *	GameEngine::getWindow( void ) const { return this->_window; }
GameEntity *		GameEngine::getPlayer( void ) { return this->_player; }
p_list &			GameEngine::getGameEntities( void ) { return this->_gameEntities; }
p_list &			GameEngine::getProjectiles( void ) { return this->_projectiles; }
int					GameEngine::getWidth( void ) const { return this->_width; }
int					GameEngine::getHeight( void ) const { return this->_height; }
float				GameEngine::getTimeRatio( void ) const { return this->_timeRatio; }

sf::Texture &		GameEngine::getTexture(int type) { return this->_textures[type]; }

void				GameEngine::resizeWindow(int width, int height)
{
	this->_width = width;
	this->_height = height;
	// TODO call the resizor of the RenderWindow :)
}

void				GameEngine::addGameEntity(int type, GameEntity * entity)
{
	fp		tab[4] = { &GameEngine::addPlayer, &GameEngine::addProjectile, &GameEngine::addEnemy, &GameEngine::addEnemyProjectile };

	(this->*tab[type])(entity);
}

void				GameEngine::addPlayer(GameEntity * entity)
{
	this->_player = entity;
}

void				GameEngine::addProjectile( GameEntity * entity )
{
	this->_projectiles.push_back(entity);
}

void				GameEngine::addEnemy( GameEntity * entity )
{
	this->_gameEntities.push_back(entity);
}

void				GameEngine::addEnemyProjectile(GameEntity * entity)
{
	this->_gameEntities.push_back(entity);
}

void				GameEngine::killPlayer( void )
{
	delete this->_player;
}

void				GameEngine::removeGameEntity(GameEntity * entity)
{
	if (!this->_gameEntities.empty())
	{
		for (std::list<GameEntity *>::iterator i = this->_gameEntities.begin(); i != this->_gameEntities.end();  )
		{
			if (*i == entity)
			{
				delete *i;
				i = this->_gameEntities.erase(i);
				break;
			}
			else
				++i;
		}
	}
}

void				GameEngine::removeProjectile(GameEntity * entity)
{
	if (!this->_projectiles.empty())
	{
		for (std::list<GameEntity *>::iterator i = this->_projectiles.begin(); i != this->_projectiles.end();  )
		{
			if (*i == entity)
			{
				delete *i;
				i = this->_projectiles.erase(i);
				break;
			}
			else
				++i;
		}
	}
}

void				GameEngine::updateAll(float elapsed)
{
	if (!this->_pause)
	{
		if (this->_gameEntities.size() > 0)
		{
			for (std::list<GameEntity *>::iterator i = this->_gameEntities.begin(); i != this->_gameEntities.end(); ++i)
				(*i)->update(*this, elapsed);
		}
		if (this->_projectiles.size() > 0)
		{
			for (std::list<GameEntity *>::iterator i = this->_projectiles.begin(); i != this->_projectiles.end(); ++i)
				(*i)->update(*this, elapsed);
		}
		if (this->_player)
			this->_player->update(*this, elapsed);
	}
}

void					GameEngine::drawAll( void )
{
	this->_window->clear(sf::Color::Black);
	if (!this->_pause)
	{
		if (this->_gameEntities.size() > 0)
		{
			for (std::list<GameEntity *>::iterator i = this->_gameEntities.begin(); i != this->_gameEntities.end(); ++i)
				(*i)->draw(*this);
		}
		if (this->_projectiles.size() > 0)
		{
			for (std::list<GameEntity *>::iterator i = this->_projectiles.begin(); i != this->_projectiles.end(); ++i)
			{
				(*i)->draw(*this);
			}
		}
		if (this->_player)
			this->_player->draw(*this);
		this->_window->display();
	}
}

void					GameEngine::pollEvent( void )
{
	sf::Event	event;

	this->_timeRatio = 1.0f;
	while (this->_window->pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			this->_window->close();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		this->_window->close();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::C))
		this->_timeRatio = 0.2f;
}

void					GameEngine::start( void )
{
	sf::Clock	clock;

	for (int i = 100; i < 550; i += 40)
		this->addEnemy(new Enemy(*this, 1000, i));
	for (int i = 100; i < 550; i += 50)
		this->addEnemy(new Enemy(*this, 2000, i));
	for (int i = 100; i < 550; i += 100)
		this->addEnemy(new Enemy(*this, 3000, i));
	for (int i = 100; i < 550; i += 50)
		this->addEnemy(new Enemy(*this, 4000, i));
	for (int i = 100; i < 550; i += 40)
		this->addEnemy(new Enemy(*this, 5000, i));
	for (int i = 100; i < 550; i += 100)
		this->addEnemy(new Enemy(*this, 6000, i));

	while (this->_window->isOpen())
	{
		this->pollEvent();
		float	elapsed = clock.restart().asSeconds();
		this->updateAll(elapsed);
		this->drawAll();
	}
}
