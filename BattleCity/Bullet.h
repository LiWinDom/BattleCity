#pragma once
#include <algorithm>
#include <SFML/Graphics.hpp>

#include "Config.h"
#include "Block.h"

class Bullet
{
public:
	Bullet(const uint8_t& x, const uint8_t& y, const uint8_t& rotation, const float& speed = BULLET_SLOW, const float& power = false);

	uint8_t getX();

	uint8_t getY();

	bool move(const std::vector<std::vector<Block*>>& map);

	void draw(sf::RenderWindow& window);
private:
	int16_t x, y;
	uint8_t rotation;
	float speed;
	bool power;

	sf::Clock clock;
	float lastMoveTime = 0;

	sf::Texture texture;
	sf::Sprite sprite;

	bool blockCollide(const std::vector<std::vector<Block*>>& map);
};

