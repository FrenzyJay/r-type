#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <cmath>
#include <ctime>
#include <iostream>
#include <cstdlib>
#include <list>
#include "Collision.hpp"

/*
class GameBoard
{
private:
	static std::vector< GameEntities >	_gameEntities;
	int									_width;
	int									_height;
}

class Projectile : public sf::Drawable, public sf::Transformable
{
public:
	Projectile

}
*/

int main()
{
	

    // on crée la fenêtre
	int		width = 900;
	int		height = 600;
	
    sf::RenderWindow window(sf::VideoMode(width, height), "PEW PEW");

	// on charge les donnes du jeu
	sf::Texture	shipsTexture;
	float		missilSpeed = 600.f;

	float		fireRate = 0.1f;
	float		lastShot = 1.f;
	
	float		shipsSpeed = 600.f;
	float		enemySpeed = 400.f;
	int			enemyLife = 1;

	if (!Collision::CreateTextureAndBitmask(shipsTexture, "samplespaceships.png"))
		return 1;

	// on cree un joueur
	sf::Sprite	playerSprite(shipsTexture);

	playerSprite.setTextureRect(sf::IntRect(0, 0, 40, 40));
	playerSprite.rotate(90);
	
	playerSprite.setPosition(70, 280);

	// un ennemi
	sf::Sprite	enemySprite(shipsTexture);
	enemySprite.setTextureRect(sf::IntRect(40, 0, 40, 40));
	enemySprite.rotate(-90);

	enemySprite.setPosition(2000, 280);

	// la texture des missiles
	sf::Texture	missilTexture;

	if (!Collision::CreateTextureAndBitmask(missilTexture, "laser.png"))
		return 1;

	// on cree un tableau de missiles :D
	std::list < sf::Sprite >	missils;

    // on crée un chrono pour mesurer le temps écoulé
    sf::Clock clock;

    // on fait tourner la boucle principale
    while (window.isOpen())
    {
        // on gère les évènements
        sf::Event event;
        while (window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
                window.close();
        }

        // on met à jour le joueur
		float elapsed = clock.restart().asSeconds();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			if (playerSprite.getPosition().y > 5.f)
				playerSprite.move(0, -shipsSpeed * elapsed);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			if (playerSprite.getPosition().y < height - 40.f - 5.f)
				playerSprite.move(0, shipsSpeed * elapsed);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			if ( lastShot + elapsed > fireRate )
			{
				sf::Sprite	missil(missilTexture);
				missil.setPosition(playerSprite.getPosition().x, playerSprite.getPosition().y + 10);
				missils.push_back(missil);
				lastShot = 0;
			}
		}
		lastShot += elapsed;

		// on met a jour l'ennemi
		enemySprite.move(-enemySpeed * elapsed, 0);

		// et les missiles
		for ( std::list< sf::Sprite >::iterator i = missils.begin(); i != missils.end(); ++i )
		{
			(*i).move(missilSpeed * elapsed, 0.f);
			if ((*i).getPosition().x > width)
				i = missils.erase(i);
		}

		// on test la collision
		if (Collision::PixelPerfectTest(playerSprite, enemySprite))
			enemyLife = 0;

		// et celle des missiles
		for ( std::list< sf::Sprite >::iterator i = missils.begin(); i != missils.end(); ++i )
		{
			if (Collision::PixelPerfectTest(enemySprite, *i))
			{
				enemyLife = 0;
				i = missils.erase(i);
			}
		}

		/*
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			if (playerSprite.getPosition().x > 50)
				playerSprite.move(-playerSpeed * elapsed, 0);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			if (playerSprite.getPosition().x < 100)
				playerSprite.move(playerSpeed * elapsed, 0);
		}
*/
        // on le dessine
        window.clear(sf::Color::Black);
        window.draw(playerSprite);
		if (enemyLife)
       		window.draw(enemySprite);
		for ( std::list< sf::Sprite >::iterator i = missils.begin(); i != missils.end(); i++ )
			window.draw(*i);
        window.display();
    }

    return 0;
}
