#pragma once
#define TANK_UP 0
#define TANK_LEFT 1
#define TANK_DOWN 2
#define TANK_RIGHT 3
#define TANK_YELLOW "TankYellow"
#define TANK_GREEN "TankGreen"
#define TANK_WHITE "TankWhite"
#define TANK_RED "TankRed"

#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>
#include <Windows.h>

#include "Block.h"

class Tank
{
public:
	int16_t x = 72, y = 200;
	uint8_t level = 0, rotation = TANK_DOWN;
	float speed = 48;
	bool animation = false;

	Tank(const std::string& view, const uint8_t& x, const uint8_t& y, const uint8_t& level = 0, const uint8_t& rotation = TANK_DOWN);

	void set(const uint8_t& x, const uint8_t& y, const uint8_t& rotation, const bool& animation);

	void up(const std::vector<std::vector<Block*>>& map);

	void left(const std::vector<std::vector<Block*>>& map);

	void down(const std::vector<std::vector<Block*>>& map);

	void right(const std::vector<std::vector<Block*>>& map);

	void draw(sf::RenderWindow& window);
private:
	std::string view = TANK_WHITE;

	sf::Texture textures[8][4][2];
	sf::Sprite sprite;

	bool blockCollide(const std::vector<std::vector<Block*>>& map);
};

