#pragma once
#include <algorithm>
#include <string>
#include <SFML/Graphics.hpp>

#include "Config.h"
#include "Bullet.h"
#include "Block.h"
#include "Explosion.h"

class Tank
{
public:
	Tank(const uint8_t& type, const uint8_t& x, const uint8_t& y, const uint8_t& level = 0, const uint8_t& rotation = TANK_DOWN, const float& freezeTime = -1, const bool& bonus = false);

	uint64_t getID();

	bool isSpawned();

	bool isDestroyed();

	float getSpeed();

	uint8_t getLives();

	bool getBonus();

	void helmet();

	void freeze();

	void levelUp();

	void addLife();

	void spawn(Tank* player1, Tank* player2, const std::vector<Tank*>& enemies);

	bool spriteCollide(const sf::Sprite& sprite, const bool& countNotSpawned = false);

	bool bulletCollide(const std::vector<Bullet*>& bullets1, const std::vector<Bullet*>& bullets2);

	bool bulletCollide(const std::vector<Bullet*>& bullets1, const std::vector<Bullet*>& bullets2, Explosion*& tankExplosion, Explosion*& bulletExplosion);

	void up(const std::vector<std::vector<Block*>>& map, Tank* player1, Tank* player2, const std::vector<Tank*>& enemies);

	void left(const std::vector<std::vector<Block*>>& map, Tank* player1, Tank* player2, const std::vector<Tank*>& enemies);

	void down(const std::vector<std::vector<Block*>>& map, Tank* player1, Tank* player2, const std::vector<Tank*>& enemies);

	void right(const std::vector<std::vector<Block*>>& map, Tank* player1, Tank* player2, const std::vector<Tank*>& enemies);

	void reset();

	Bullet* shoot();

	void bulletDestroyed();

	void draw(sf::RenderWindow& window);

	Bullet* think(const std::vector<std::vector<Block*>>& map, Tank* player1, Tank* player2, const std::vector<Tank*>& enemies);

	void destroy(const bool full = false);

	void destroy(Explosion*& explosion, const bool full = false);
private:
	uint8_t startX, startY, startRotation;
	uint8_t x, y;
	uint8_t level, rotation;
	uint8_t type;
	bool spawned = false;
	bool bonus;
	bool animation = false;
	bool isMove = true;

	sf::Clock clock;
	float lastMove = 0, lastShot = 0, destroyedTime = 0, protectedUntil = -1, frozenUntil = 0;
	uint8_t bullets = 0;

	uint8_t color = 0;
	uint8_t lives = 1;
	bool destroyed = false;

	sf::Texture textures[4][4][2], protectionTextures[2], spawnFrames[6];
	sf::Sprite hitbox, sprite, protection, spawnSprite;

	uint64_t id = std::time(nullptr) * std::rand();

	Bullet* move(const std::vector<std::vector<Block*>>& map, Tank* player1, Tank* player2, const std::vector<Tank*>& enemies);

	void changeRotation();

	void changeColor();

	bool blockCollide(const std::vector<std::vector<Block*>>& map, const sf::Sprite& sprite);

	bool tankCollide(Tank* player1, Tank* player2, const std::vector<Tank*>& enemies, const sf::Sprite& sprite);
};

