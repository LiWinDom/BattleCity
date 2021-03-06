#pragma once
#include <algorithm>
#include <SFML/Graphics.hpp>

#include "Config.h"

class Block
{
public:
	Block(const uint8_t& type, const uint8_t& x, const uint8_t& y);

	uint8_t getType();

	void placeProtection();

	void removeProtection();

	void draw(sf::RenderWindow& window, const sf::Clock& globalClock);

	bool tankCollide(const sf::Sprite& sprite);

	bool bulletCollide(const sf::Sprite& sprite, const uint8_t& rotation, const bool& power, bool& eagleDestroyed);
private:
	uint8_t type;
	uint8_t x, y;

	sf::Texture texture;
	sf::Sprite sprite;

	// For brick
	bool state[4] = { true, true, true, true };
	sf::Texture textures[2];
	sf::Sprite sprites[4];

	// For protection
	sf::Clock clock;
	float protectedUntil = -1;
	float unprotectedUntil = -1;
};

