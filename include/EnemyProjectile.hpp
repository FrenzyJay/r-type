#ifndef ENEMY_PROJECTILE_HPP
# define ENEMY_PROJECTILE_HPP

# include "GameEntity.hpp"
# include "Enemy.hpp"

class GameEngine;

class EnemyProjectile: public GameEntity
{
private:
	int		_damage;

public:
	EnemyProjectile();
	EnemyProjectile(GameEngine & engine, Enemy * enemy);
	EnemyProjectile(EnemyProjectile const & rhs);
	~EnemyProjectile();

	EnemyProjectile &	operator=(EnemyProjectile const & rhs);

	int				getDamage( void ) const;
	void			setDamage(int damage);

	virtual void	update(GameEngine & engine, float elapsed);
};

#endif
