#pragma once
#include <algorithm>
#include <SFML/Graphics.hpp>

#include "Config.h"

class Block
{
public:
	Block(const uint8_t& type, const uint8_t& x, const uint8_t& y);

	uint8_t getType();

	void draw(sf::RenderWindow& window, const sf::Clock& clock);

	bool tankCollide(const sf::Sprite& sprite);

	bool bulletCollide(const sf::Sprite& sprite, const uint8_t& rotation, const bool& power, bool& gameOver);
private:
	uint8_t type;
	uint8_t x, y;

	sf::Texture texture;
	sf::Sprite sprite;

	// For brick
	bool state[4] = { true, true, true, true };
	sf::Texture textures[2];
	sf::Sprite sprites[4];
};

