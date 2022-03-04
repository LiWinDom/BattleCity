#pragma once
#include <algorithm>
#include <SFML/Graphics.hpp>

#include "Config.h"

class Explosion
{
public:
	Explosion(const uint8_t& x, const uint8_t& y, const bool& big = false);

	bool isEnded();

	void draw(sf::RenderWindow& window);
private:
	uint8_t x, y;
	uint8_t frame = 0;
	bool big;

	sf::Texture frames[9];
	sf::Sprite sprite;

	sf::Clock clock;
	float lastChange = 0;
};
