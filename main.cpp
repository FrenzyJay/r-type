#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <cmath>
#include <ctime>
#include <iostream>
#include <cstdlib>
#include <list>
#include <sstream>
#include "Collision.hpp"

// LE main
int main()
{
	srand(time(NULL));

    // on crée la fenêtre
	int		width = 900;
	int		height = 600;
	
    sf::RenderWindow window(sf::VideoMode(width, height), "PEW PEW");

	// on charge les donnes du jeu
	int			score = 0;
	
	sf::Texture	shipsTexture;
	float		missilSpeed = 600.f;

	float		fireRate = 0.2f;
	float		lastShot = 1.f;
	
	float		shipsSpeed = 600.f;
	float		enemySpeed = 250.f;

	if (!Collision::CreateTextureAndBitmask(shipsTexture, "samplespaceships.png"))
		return 1;

	sf::Texture	ponyTexture;
	int		maxPonyLife = 10000;
	int		ponyLife = maxPonyLife;
	float	ponySpeed = 100.f;

	if (!Collision::CreateTextureAndBitmask(ponyTexture, "evil-pony.png"))
		return 1;

	sf::Sprite	ponySprite(ponyTexture);
	ponySprite.setScale(500 / 150, 500 / 150);
	ponySprite.setPosition(1000, 75);

	// on cree un joueur
	sf::Sprite	playerSprite(shipsTexture);

	playerSprite.setTextureRect(sf::IntRect(0, 0, 40, 40));
	playerSprite.rotate(90);
	
	playerSprite.setPosition(70, 280);

	// la texture des missiles
	sf::Texture	missilTexture;

	if (!Collision::CreateTextureAndBitmask(missilTexture, "laser.png"))
		return 1;

	// on cree une liste de pointeurs de missiles :D
	std::list < sf::Sprite * >	missils;

	// on cree une liste d'ennemi :P
	std::list < sf::Sprite >	enemies;
	// le spawn des ennemis
	float		spawnRate = 0.5f;
	float		lastSpawn = 1.f;

    // on crée un chrono pour mesurer le temps écoulé
    sf::Clock clock;

	// on charge la font
	sf::Font	font;

	if (!font.loadFromFile("fonts/dimitri.ttf"))
		return 1;

	// on cree le texte d'affichage du score
	sf::Text	scoreText;
	scoreText.setFont(font);
	scoreText.setCharacterSize(42);
	scoreText.setPosition(30.f, 1.f);
	scoreText.setColor(sf::Color::White);


	std::stringstream	ss;
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

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        {
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

		// on tire des missiles :O pew pew pew
		lastShot += elapsed;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			if ( lastShot + elapsed > fireRate )
			{
				sf::Sprite *	missil = new sf::Sprite(missilTexture);
				missil->setPosition(playerSprite.getPosition().x, playerSprite.getPosition().y + 10);
				missils.push_back(missil);
				lastShot = 0;
			}
		}

		// on bouge le poney o_o
		if (playerSprite.getPosition().y < ponySprite.getPosition().y + 200)
			ponySprite.move( -ponySpeed * elapsed, -ponySpeed * elapsed);
		else
			ponySprite.move( -ponySpeed * elapsed, ponySpeed * elapsed);

		// on pop des ennemis
		lastSpawn += elapsed;
		if (lastSpawn + elapsed > spawnRate)
		{
			sf::Sprite	enemySprite(shipsTexture);
			enemySprite.setTextureRect(sf::IntRect(40, 0, 40, 40));
			enemySprite.rotate(-90);
			enemySprite.setPosition(1000, (rand() % (height - 200)) + 100);
			enemies.push_back(enemySprite);
			lastSpawn = 0;
		}
		// on les met a jour
		for ( std::list< sf::Sprite >::iterator i = enemies.begin(); i != enemies.end(); ++i )
		{
			(*i).move(-enemySpeed * elapsed, 0);
			if ((*i).getPosition().x < 0)
			{
				i = enemies.erase(i);
			}
		}

		// et on met a jour les missiles
		for ( std::list< sf::Sprite * >::iterator i = missils.begin(); i != missils.end(); ++i )
		{
			(*i)->move(missilSpeed * elapsed, 0.f);
			if ((*i)->getPosition().x > width)
			{
				delete *i;
				i = missils.erase(i);
			}
		}

		// on test les collision avec le joueur
		for ( std::list< sf::Sprite >::iterator i = enemies.begin(); i != enemies.end(); ++i )
		{
			if (Collision::PixelPerfectTest(playerSprite, *i))
				i = enemies.erase(i);
		}

		// et celle des missiles
		for ( std::list< sf::Sprite * >::iterator i = missils.begin(); i != missils.end(); ++i )
		{
			// avec le poney
			if (Collision::PixelPerfectTest(ponySprite, *(*i)))
			{
				// si il a de la vie c'est degueu mais le poney n'est pas dans la liste des autres entites il est special il aime se differencier des autres c'est son droit en tant que poney libre :)
				if (ponyLife >= 0)
				{
					ponySprite.setColor(sf::Color(255, 255, 255, ponyLife * 255));
					ponyLife -= 500;
					score += 500;
					delete *i;
					i = missils.erase(i);
					ponySprite.move( 10, 0);
				}
			}
			else
			{
				for ( std::list< sf::Sprite >::iterator j = enemies.begin(); j != enemies.end(); ++j )
				{
					if (Collision::PixelPerfectTest(*j, *(*i)))
					{
						score += 100;
						delete *i;
						i = missils.erase(i);
						j = enemies.erase(j);
						break;
					}
				}
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
		ss << score;
		scoreText.setString(ss.str());
		ss.clear();
		ss.str(std::string());
        // on dessine les objets dans la scene
        window.clear(sf::Color::Black);
        window.draw(playerSprite);
		for ( std::list< sf::Sprite >::iterator i = enemies.begin(); i != enemies.end(); i++ )
       		window.draw(*i);
		for ( std::list< sf::Sprite * >::iterator i = missils.begin(); i != missils.end(); i++ )
			window.draw(*(*i));
		// stealth mode du poney mort ca aussi c'est degueu mais pareil qu'en haut le poney libre fait ce qu'il lui chante
		if (ponyLife >= 0)
			window.draw(ponySprite);
		window.draw(scoreText);
        window.display();
    }

    return 0;
}
