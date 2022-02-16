#pragma once
#include <algorithm>
#include <string>
#include <SFML/Graphics.hpp>

#include "Config.h"
#include "Bullet.h"
#include "Block.h"
#include "Player.h"

class Enemy
{
public:
	Enemy(const uint8_t& x, const uint8_t& y, const uint8_t& level = 0, const uint8_t& rotation = TANK_DOWN, const bool& bonus = false);

	bool isDestroyed();

	bool spriteCollide(const sf::Sprite& sprite);

	void bulletCollide(const std::vector<Bullet*>& bullets);

	Bullet* think(const std::vector<std::vector<Block*>>& map, const std::vector<Player*>& players, const std::vector<Enemy*>& enemies);

	void bulletDestroyed();

	void draw(sf::RenderWindow& window);
private:
	uint8_t x, y;
	uint8_t level, rotation;
	bool bonus;
	bool animation = false;

	bool isMove = false;
	sf::Clock clock;
	float lastMove, lastShot = 0;
	uint8_t bullets = 0;

	uint8_t color = 0;
	int8_t lives;
	bool destroyed = false;

	sf::Texture textures[4][4][2];
	sf::Sprite hitbox, sprite;

	Bullet* move(const std::vector<std::vector<Block*>>& map, const std::vector<Player*>& players, const std::vector<Enemy*>& enemies);

	void changeRotation();

	Bullet* shoot();

	bool blockCollide(const std::vector<std::vector<Block*>>& map, const sf::Sprite& sprite);

	bool tankCollide(const std::vector<Player*>& players, const std::vector<Enemy*>& enemies, const sf::Sprite& sprite);

	void destroy();

	void changeColor();
};

