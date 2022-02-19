#pragma once
#include <algorithm>
#include <string>
#include <SFML/Graphics.hpp>

#include "Config.h"
#include "Bullet.h"
#include "Block.h"

class Tank
{
public:
	Tank(const uint8_t& type, const uint8_t& x, const uint8_t& y, const uint8_t& level = 0, const uint8_t& rotation = TANK_DOWN, const bool& bonus = false);

	uint64_t getID();

	float getSpeed();

	bool isDestroyed();

	bool spriteCollide(const sf::Sprite& sprite);

	bool bulletCollide(const std::vector<Bullet*>& bullets);

	void up(const std::vector<std::vector<Block*>>& map, const std::vector<Tank*>& players, const std::vector<Tank*>& enemies);

	void left(const std::vector<std::vector<Block*>>& map, const std::vector<Tank*>& players, const std::vector<Tank*>& enemies);

	void down(const std::vector<std::vector<Block*>>& map, const std::vector<Tank*>& players, const std::vector<Tank*>& enemies);

	void right(const std::vector<std::vector<Block*>>& map, const std::vector<Tank*>& players, const std::vector<Tank*>& enemies);

	Bullet* shoot();

	void bulletDestroyed();

	void draw(sf::RenderWindow& window);

	Bullet* think(const std::vector<std::vector<Block*>>& map, const std::vector<Tank*>& players, const std::vector<Tank*>& enemies);
private:
	uint8_t startX, startY, startRotation;
	uint8_t x, y;
	uint8_t level, rotation;
	uint8_t type;
	bool bonus;
	bool animation = false;
	bool isMove = true;

	sf::Clock clock;
	float lastMove = 0, lastShot = 0, destroyedTime = -10;
	uint8_t bullets = 0;

	uint8_t color = 0;
	int8_t lives = 1;
	bool destroyed = false;

	sf::Texture textures[4][4][2];
	sf::Sprite hitbox, sprite;

	uint64_t id = std::time(nullptr);

	Bullet* move(const std::vector<std::vector<Block*>>& map, const std::vector<Tank*>& players, const std::vector<Tank*>& enemies);

	void changeRotation();

	void changeColor();

	bool blockCollide(const std::vector<std::vector<Block*>>& map, const sf::Sprite& sprite);

	bool tankCollide(const std::vector<Tank*>& players, const std::vector<Tank*>& enemies, const sf::Sprite& sprite);

	void destroy();
};

