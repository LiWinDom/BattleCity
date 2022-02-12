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
	Tank(const std::string& view, const uint8_t& x, const uint8_t& y, const uint8_t& level = 0, const float& speed = TANK_SLOW, const uint8_t& rotation = TANK_DOWN);

	float getSpeed();

	void up(const std::vector<std::vector<Block*>>& map);

	void left(const std::vector<std::vector<Block*>>& map);

	void down(const std::vector<std::vector<Block*>>& map);

	void right(const std::vector<std::vector<Block*>>& map);

	void shoot();

	void bulletMove(const std::vector<std::vector<Block*>>& map);

	void draw(sf::RenderWindow& window);

	void bulletDraw(sf::RenderWindow& window);
private:
	int16_t x, y;
	uint8_t level, rotation;
	std::string view;
	float speed;
	bool animation = false;

	Bullet* bullet = nullptr;
	sf::Clock clock;
	float lastShot;

	sf::Texture textures[8][4][2];
	sf::Sprite sprite;

	bool blockCollide(const std::vector<std::vector<Block*>>& map);
};

