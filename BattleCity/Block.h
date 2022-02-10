#pragma once
#define BLOCK_AIR 0
#define BLOCK_BRICK 1
#define BLOCK_WALL 2
#define BLOCK_BUSH 3
#define BLOCK_WATER 4
#define BLOCK_ICE 5
#define BLOCK_PROTECTION 6
#define BLOCK_EAGLE 7

#include <iostream>
#include <algorithm>
#include <SFML/Graphics.hpp>
#include <Windows.h>

class Block
{
public:
	Block(const uint8_t& view, const uint8_t& x, const uint8_t& y);

	void draw(sf::RenderWindow& window);

	bool tankCollide(const sf::Sprite& sprite);
private:
	uint8_t view;
	uint8_t x, y;

	sf::Texture texture;
	sf::Sprite sprite;

	// For brick
	bool state[4] = { true, true, true, true };
	sf::Texture textures[2];
	sf::Sprite sprites[4];
};

