#pragma once
#include <algorithm>
#include <SFML/Graphics.hpp>

#include "Config.h"
#include "Block.h"
#include "Tank.h"
#include "Explosion.h"

class Bonus
{
public:
	Bonus(const std::vector<std::vector<Block*>>& map, Tank* player1, Tank* player2, const std::vector<Tank*>& enemies);

	bool isTaken();

	void collideCheck(Tank* player1, Tank* player2, const std::vector<Tank*>& enemies, const std::vector<std::vector<Block*>>& map, const sf::Clock& globalClock, float& playersFrozenUntil, float& enemiesFrozenUntil, std::vector<Explosion*>& explosions);

	void draw(sf::RenderWindow& window);
private:
	uint8_t type;
	bool taken = false;

	sf::Texture texture;
	sf::Sprite sprite;

	sf::Clock clock;
};

