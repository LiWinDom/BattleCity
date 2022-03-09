#pragma once
#include <algorithm>
#include <SFML/Graphics.hpp>

#include "Config.h"
#include "Block.h"
#include "Explosion.h"

class Bullet
{
public:
	Bullet(const uint8_t& x, const uint8_t& y, const uint8_t& rotation, const float& speed = BULLET_SLOW, const float& power = false);

	bool isDestroyed();

	void destroy();

	void destroy(Explosion*& explosion);

	bool spriteCollide(const sf::Sprite& sprite);

	void move(const std::vector<std::vector<Block*>>& map, const std::vector<Bullet*>& bullets1, const std::vector<Bullet*>& bullets2, bool& eagleDestroyed);

	void move(const std::vector<std::vector<Block*>>& map, const std::vector<Bullet*>& bullets1, const std::vector<Bullet*>& bullets2, bool& eagleDestroyed, Explosion*& explosion);

	void draw(sf::RenderWindow& window);
private:
	uint8_t x, y;
	uint8_t rotation;
	float speed;
	bool power;

	sf::Clock clock;
	float lastMoveTime = 0;

	bool destroyed = false;

	sf::Texture texture;
	sf::Sprite sprite;

	void blockCollide(const std::vector<std::vector<Block*>>& map, bool& eagleDestroyed);

	void blockCollide(const std::vector<std::vector<Block*>>& map, bool& eagleDestroyed, Explosion*& explosion);

	void bulletCollide(const std::vector<Bullet*>& bullets);
};

