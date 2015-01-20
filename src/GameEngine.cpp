#include <iostream>
#include "GameEngine.hpp"
#include "Player.hpp"

GameEngine::GameEngine()
{}

GameEngine::GameEngine(int width, int height)
{
	this->_window = new sf::RenderWindow(sf::VideoMode(width, height), "PEW PEW PEW");
	this->_width = width;
	this->_height = height;
	Collision::CreateTextureAndBitmask(this->_textures[0], "assets/player.png");
	Collision::CreateTextureAndBitmask(this->_textures[1], "assets/samplespaceships.png");
	Collision::CreateTextureAndBitmask(this->_textures[2], "assets/evil-pony.png");

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
	this->_gameEntities = rhs.getGameEntities();
	return *this;
}

sf::RenderWindow *	GameEngine::getWindow( void ) const { return this->_window; }
p_list				GameEngine::getGameEntities( void ) const { return this->_gameEntities; }
int					GameEngine::getWidth( void ) const { return this->_width; }
int					GameEngine::getHeight( void ) const { return this->_height; }

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
	for (std::list<GameEntity *>::iterator i = this->_gameEntities.begin(); i != this->_gameEntities.end(); ++i)
	{
		if (*i == entity)
		{
			delete *i;
			i = this->_gameEntities.erase(i);
		}
	}
}

void				GameEngine::removeProjectile(GameEntity * entity)
{
	for (std::list<GameEntity *>::iterator i = this->_projectiles.begin(); i != this->_projectiles.end(); ++i)
	{
		if (*i == entity)
		{
			delete *i;
			i = this->_projectiles.erase(i);
		}
	}
}

void				GameEngine::updateAll(float elapsed)
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

void					GameEngine::drawAll( void )
{
	if (this->_gameEntities.size() > 0)
	{
		for (std::list<GameEntity *>::iterator i = this->_gameEntities.begin(); i != this->_gameEntities.end(); i++)
			(*i)->draw(*this);
	}
	if (this->_projectiles.size() > 0)
	{
		for (std::list<GameEntity *>::iterator i = this->_projectiles.begin(); i != this->_projectiles.end(); i++)
		{
			(*i)->draw(*this);
		}
	}
	if (this->_player)
		this->_player->draw(*this);
}

void					GameEngine::pollEvent( void )
{
	sf::Event	event;

	while (this->_window->pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			this->_window->close();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		this->_window->close();
}

void					GameEngine::start( void )
{
	sf::Clock	clock;

	while (this->_window->isOpen())
	{
		this->pollEvent();
		float	elapsed = clock.restart().asSeconds();
		(void)elapsed;
		this->_window->clear(sf::Color::Black);
		this->drawAll();
		this->_window->display();
	}
}
