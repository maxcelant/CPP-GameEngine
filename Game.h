#pragma once

#include "Entity.h"
#include "EntityManager.h"

#include <SFML/Graphics.hpp>

struct PlayerConfig { int SR, CR, FR, FG, FB, OR, OG, OB, OT, V; float S; };
struct EnemyConfig { int SR, CR, OR, OG, OB, OT, VMIN, VMAX, L, SI; float SMIN; };
struct BulletConfig { int SR, CR, FR, FG, FB, OR, OG, OB, OT, V, L; float S; };


class Game
{
	sf::RenderWindow	  _window;
	EntityManager		  _entityManager;
	sf::Font			  _font;
	sf::Text			  _text;
	PlayerConfig		  _playerConfig;
	EnemyConfig			  _enemyConfig;
	BulletConfig		  _bulletConfig;
	int				      _score = 0;
	int					  _currentFrame = 0;
	int					  _lastEnemySpawnTime = 0;
	bool				  _paused = false;
	bool				  _running = true;

	std::shared_ptr<Entity> _player;

	void init(const std::string& config); // init game state using config file
	void setPaused(bool paused);		  // pause the game

	void sMovement();
	void sUserInput();
	void sLifespan();
	void sRender();
	void sEnemySpawner();
	void sCollision();

	void spawnPlayer();
	void spawnEnemy();
	void spawnSmallEnemies(std::shared_ptr<Entity> entity);
	void spawnBullet(std::shared_ptr<Entity> entity, const Vec2& mousePos);
	void spawnSpecialWeapon(std::shared_ptr<Entity> entity);

public:

	Game(const std::string& config); // constructor, takes in config file

	void run();
};
