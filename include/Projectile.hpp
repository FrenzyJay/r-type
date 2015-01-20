#ifndef PROJECTILE_HPP
# define PROJECTILE_HPP

# include "GameEntity.hpp"

class GameEngine;

class Projectile: public GameEntity
{
private:
	int		_damage;

public:
	Projectile();
	Projectile(GameEngine & engine);
	Projectile(Projectile const & rhs);
	~Projectile();

	Projectile &	operator=(Projectile const & rhs);

	int				getDamage( void ) const;
	void			setDamage(int damage);

	virtual void	update(GameEngine & engine, float elapsed);
};

#endif
