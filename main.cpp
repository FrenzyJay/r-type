#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <cmath>
#include <ctime>
#include <cstdlib>
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
	float		shipsSpeed = 1000.f;
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

		// on met a jour l'ennemi
		enemySprite.move(-enemySpeed * elapsed, 0);

		// on test la collision
		if (Collision::PixelPerfectTest(playerSprite, enemySprite))
			enemyLife = 0;

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
        window.display();
    }

    return 0;
}
