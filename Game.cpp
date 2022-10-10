#include "Game.h"

#include <iostream>
#include <fstream>

Game::Game(const std::string& config) // constructor
{
	init(config);
}

void Game::init(const std::string& path)
{
	// TODO: read in config file here
	// use the premade struct variables for PlayerConfig, etc
	std::ifstream fin(path);

	// fin >> _playerConfig.SR >> _playerConfig.CR >> ...

	_window.create(sf::VideoMode(1280, 720), "Polyshooter");
	_window.setFramerateLimit(60);

	spawnPlayer();
}

void Game::run()
{
	while (_running)
	{
		_entityManager.update();

		if (!_paused) // what to do when we aren't paused
		{
			sEnemySpawner();
			sMovement();
			sCollision();
			sUserInput();
		}

		sRender();
		
		_currentFrame++; // increment current frame
	}
}

void Game::setPaused(bool paused)
{
	_paused = paused;
}

void Game::spawnPlayer()
{
	auto entity = _entityManager.addEntity("player");

	float mx = _window.getSize().x / 2.0f;
	float my = _window.getSize().y / 2.0f;
	
	// spawns at (200, 200) with velocity of (1, 1) at angle 0
	entity->cTransform = std::make_shared<CTransform>(Vec2(mx, my), Vec2(1.0f, 1.0f), 0.0f);

	// shape with radius 32 and 8 sides, dark grey fill and red border with 4 border thickness
	entity->cShape = std::make_shared<CShape>(32.0f, 8, sf::Color(10, 10, 10), sf::Color(255, 0, 0), 4.0f);

	// add input component, so we can move it
	entity->cInput = std::make_shared<CInput>();

	// add wall collision
	//entity->cCollision = std::make_shared<CCollision>(32.0f);

	_player = entity; // set this entity to our player
}

void Game::spawnEnemy()
{
	// create enemy similar to player
	auto entity = _entityManager.addEntity("enemy");
	float ex = rand() % _window.getSize().x; // give it a min and max thats equal to the radius of the object
	float ey = rand() % _window.getSize().y; // give it a min and max thats equal to the radius of the object

	entity->cTransform = std::make_shared<CTransform>(Vec2(ex, ey), Vec2(3.0f, 3.0f), 5.0f);
	entity->cShape = std::make_shared<CShape>(18.0f, 6, sf::Color(0, 0, 255), sf::Color(255, 255, 255), 4.0f);
	entity->cCollision = std::make_shared<CCollision>(18.0f);

	// record when the most recent enemy was spawned
	_lastEnemySpawnTime = _currentFrame;
}

void Game::spawnSmallEnemies(std::shared_ptr<Entity> e)
{
	// spawn small enemies at the locationm of the input enemy e

	// when we create the smaller enemy, we have to read values of the original enemy
	// - spawn a number of small enemies equal to the vertices of the og enemy
	// - set each small enemy to the same color as the origianl, half the size
	// - small enemies are worth double points of the original enemy
}

void Game::spawnBullet(std::shared_ptr<Entity> entity, const Vec2& mousePos)
{
	auto bullet = _entityManager.addEntity("bullet");

	// in order to get velocity we must first find the mx,my and px,py
	// calculate the distance, 
	float distance = entity->cTransform->pos.dist(mousePos);
	
	// get the (m.x-p.x, m.y-p.y) = D
	Vec2 newVec = entity->cTransform->pos.length(mousePos);
	
	// normalize the vector to get nx, ny
	Vec2 normalizedVec = newVec.normalize(distance);
	
	// we also need the angle (theta) of the trajectory!
	float angle = normalizedVec.theta();

	// then multiply by speed vector
	normalizedVec.x *= 10.0; 
	normalizedVec.y *= 10.0;

	// spawn the bullet at the position of the player entity
	bullet->cTransform = std::make_shared<CTransform>(Vec2(entity->cTransform->pos.x, entity->cTransform->pos.y), Vec2(normalizedVec.x, normalizedVec.y), angle);

	bullet->cShape = std::make_shared<CShape>(10.0f, 8, sf::Color(210, 135, 255), sf::Color(255, 255, 255), 2.0f);
}

void Game::spawnSpecialWeapon(std::shared_ptr<Entity> entity)
{

}

void Game::sRender()
{
	_window.clear();

	for (auto e : _entityManager.getEntities())
	{
		e->cShape->circle.setPosition(e->cTransform->pos.x, e->cTransform->pos.y);

		e->cTransform->angle += 1.0f;
		e->cShape->circle.setRotation(e->cTransform->angle);

		_window.draw(e->cShape->circle);
	}

	_window.display();
}

void Game::sMovement()
{

	for (auto& e : _entityManager.getEntities()) // movement of every entitty
	{
		e->cTransform->pos.x += e->cTransform->velocity.x;
		e->cTransform->pos.y += e->cTransform->velocity.y;
	}

	_player->cTransform->velocity = { 0, 0 };

	// player change directions
	if (_player->cInput->up)
	{
		_player->cTransform->velocity.y = -5; // change this to speed later
	}
	if (_player->cInput->down)
	{
		_player->cTransform->velocity.y = 5; // change this to speed later
	}
	if (_player->cInput->left)
	{
		_player->cTransform->velocity.x = -5;
	}
	if (_player->cInput->right)
	{
		_player->cTransform->velocity.x = 5;
	}

	// player movement
	_player->cTransform->pos.x += _player->cTransform->velocity.x;
	_player->cTransform->pos.y += _player->cTransform->velocity.y;
}

void Game::sCollision()
{
	// TODO: Implement all the proper collisions between
	// entities, be sure to use collision radius, NOT shape radius
	for (auto& e : _entityManager.getEntities())
	{
		if (e->cCollision != NULL)
		{
			if (e->cTransform->pos.x > (_window.getSize().x - e->cCollision->radius) || e->cTransform->pos.x < e->cCollision->radius)
			{
				e->cTransform->velocity.x *= -1.0; // inverse x direction
			}
			if (e->cTransform->pos.y > (_window.getSize().y - e->cCollision->radius) || e->cTransform->pos.y < e->cCollision->radius)
			{
				e->cTransform->velocity.y *= -1.0; // inverse y direction
			}
		}
	}
}

void Game::sEnemySpawner()
{
	if (_currentFrame - _lastEnemySpawnTime > 180.0f) // spawns every 3 seconds
	{
		spawnEnemy();
	}
}

void Game::sLifespan()
{
	// implement all lifespan functionality
	// for all entities
	//		if entity has no lifespan component, skip it
	//		if entity has > - remaining lifespan, subtract 1
	//		if entity has lifespan and is alive
	//			scale its alpha channel properly
	//		if it has lifespan and its time is up
	//			destroy the entity
}

void Game::sUserInput()
{
	sf::Event event;
	while (_window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			_running = false;
		}

		if (event.type == sf::Event::KeyPressed) // key pressed down
		{
			switch (event.key.code)
			{
			case sf::Keyboard::W:
				std::cout << "W Key was pressed\n";
				_player->cInput->up = true;
				break;
			case sf::Keyboard::A:
				std::cout << "A Key was pressed\n";
				_player->cInput->left = true;
				break;
			case sf::Keyboard::S:
				std::cout << "S Key was pressed\n";
				_player->cInput->down = true;
				break;
			case sf::Keyboard::D:
				std::cout << "D Key was pressed\n";
				_player->cInput->right = true;
				break;
			default: break;
			}
		}

		if (event.type == sf::Event::KeyReleased) // key released
		{
			switch (event.key.code)
			{
			case sf::Keyboard::W:
				std::cout << "W Key was released\n";
				_player->cInput->up = false;
				break;
			case sf::Keyboard::A:
				std::cout << "A Key was released\n";
				_player->cInput->left = false;
				break;
			case sf::Keyboard::S:
				std::cout << "S Key was released\n";
				_player->cInput->down = false;
				break;
			case sf::Keyboard::D:
				std::cout << "D Key was released\n";
				_player->cInput->right = false;
				break;
			default: break;
			}
		}

		if (event.type == sf::Event::MouseButtonPressed) // mouse clicks
		{
			if (event.mouseButton.button == sf::Mouse::Left)
			{
				std::cout << "Left mouse clicked at (" << event.mouseButton.x << ", " << event.mouseButton.y << ")\n";
				spawnBullet(_player, Vec2(event.mouseButton.x, event.mouseButton.y));
			}
			
			if (event.mouseButton.button == sf::Mouse::Right)
			{
				std::cout << "Right mouse clicked at (" << event.mouseButton.x << ", " << event.mouseButton.y << ")\n";
				spawnBullet(_player, Vec2(event.mouseButton.x, event.mouseButton.y));
			}
		}
	}
}


