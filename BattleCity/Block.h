#pragma once
#include <algorithm>
#include <SFML/Graphics.hpp>

#include "Config.h"

class Block
{
public:
	Block(const uint8_t& view, const uint8_t& x, const uint8_t& y);

	void draw(sf::RenderWindow& window);

	bool tankCollide(const sf::Sprite& sprite);

	bool bulletCollide(const sf::Sprite& sprite, const uint8_t& rotation, const bool& power);
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

