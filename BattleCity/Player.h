#pragma once
#include <algorithm>
#include <string>
#include <SFML/Graphics.hpp>

#include "Config.h"
#include "Bullet.h"
#include "Block.h"

class Player
{
public:
	Player(const std::string& view, const uint8_t& x, const uint8_t& y, const uint8_t& level = 0, const uint8_t& rotation = TANK_DOWN);

	float getSpeed();

	bool isDestroyed();

	bool spriteCollide(const sf::Sprite& sprite);

	bool bulletCollide(const std::vector<Bullet*>& bullets);

	void up(const std::vector<std::vector<Block*>>& map, const std::vector<Player*>& players);

	void left(const std::vector<std::vector<Block*>>& map, const std::vector<Player*>& players);

	void down(const std::vector<std::vector<Block*>>& map, const std::vector<Player*>& players);

	void right(const std::vector<std::vector<Block*>>& map, const std::vector<Player*>& players);

	Bullet* shoot();

	void bulletDestroyed();

	void draw(sf::RenderWindow& window);
private:
	uint8_t startX, startY, startRotation;
	uint8_t x, y;
	uint8_t level, rotation;
	std::string view;
	bool animation = false;

	sf::Clock clock;
	float lastShot = 0;
	uint8_t bullets = 0;

	int8_t lives;
	bool destroyed = false;

	sf::Texture textures[4][4][2];
	sf::Sprite hitbox, sprite;

	bool blockCollide(const std::vector<std::vector<Block*>>& map, const sf::Sprite& sprite);

	bool tankCollide(const std::vector<Player*>& players, const sf::Sprite& sprite);

	void destroy();
};

