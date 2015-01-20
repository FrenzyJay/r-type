#ifndef GAME_ENGINE_HPP
# define GAME_ENGINE_HPP

# include <list>
# include <SFML/Window.hpp>
# include <SFML/Graphics.hpp>

# include "GameEntity.hpp"
# include "Collision.hpp"

class GameEntity;
class GameEngine;

enum { PLAYER, PROJECTILE, ENEMY, ENEMY_PROJECTILE };
typedef void (GameEngine::*fp)(GameEntity *);
typedef std::list< GameEntity * > p_list;

class GameEngine
{
public:
	GameEngine();
	GameEngine(GameEngine const & rhs);
	~GameEngine();
	GameEngine &	operator=(GameEngine const & rhs);

	GameEngine(int width, int height);

	sf::RenderWindow *	getWindow( void ) const;
	p_list				getGameEntities( void ) const;
	int					getWidth( void ) const;
	int					getHeight( void ) const;
	
	sf::Texture &		getTexture(int type);

	void				resizeWindow(int width, int height);

	void				addGameEntity(int type, GameEntity * entity);
	void				addEnemy(GameEntity * entity);
	void				addEnemyProjectile(GameEntity * entity);
	void				addProjectile(GameEntity * entity);
	void				addPlayer(GameEntity * entity);
	void				removeGameEntity(GameEntity * entity);
	void				removeProjectile(GameEntity * entity);
	void				killPlayer( void );

	void				updateAll(float elapsed);
	void				drawAll( void );

	void				start( void );
	void				pollEvent( void );

private:
	sf::RenderWindow *	_window;		// pointer to the window
	GameEntity *		_player;		// pointer to the player
	p_list				_gameEntities;	// enemies and enemies' projectiles
	p_list				_projectiles;	// player's projectiles
	int					_width;			// window's width
	int					_height;		// window's height
	sf::Texture			_textures[3];	// game's textures
};

# include "Player.hpp"

#endif
