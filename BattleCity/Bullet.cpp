#include "Bullet.h"

Bullet::Bullet(const uint8_t& x, const uint8_t& y, const uint8_t& rotation, const float& speed, const float& power) {
	this->x = x;
	this->y = y;
	this->rotation = rotation;
	this->speed = speed;
	this->power = power;

	if (!this->texture.loadFromFile("resources/graphics/Bullets.png", sf::IntRect(this->rotation << 2, 0, 4, 4))) throw 1;
	this->sprite.setOrigin(2, 2);
	this->sprite.setScale(4, 4);
	this->sprite.setPosition(this->x * 4, this->y * 4);
	this->sprite.setTexture(this->texture);

	lastMoveTime = clock.getElapsedTime().asSeconds();

	return;
}

uint8_t Bullet::getX() {
	return this->x;
}

uint8_t Bullet::getY() {
	return this->y;
}

bool Bullet::move(const std::vector<std::vector<Block*>>& map) {
	while (this->clock.getElapsedTime().asSeconds() >= lastMoveTime + 1 / this->speed) {
		if (this->rotation == BULLET_UP) {
			--this->y;
		}
		else if (this->rotation == BULLET_LEFT) {
			--this->x;
		}
		else if (this->rotation == BULLET_DOWN) {
			++this->y;
		}
		else if (this->rotation == BULLET_RIGHT) {
			++this->x;
		}
		this->sprite.setPosition(this->x * 4, this->y * 4);
		if (blockCollide(map)) return false;
		lastMoveTime += 1 / this->speed;
	}
	return true;
}

void Bullet::draw(sf::RenderWindow& window) {
	window.draw(sprite);
	return;
}

bool Bullet::blockCollide(const std::vector<std::vector<Block*>>& map) {
	bool collide = false;
	for (uint8_t i = 0; i < 26; ++i) {
		for (uint8_t j = 0; j < 26; ++j) {
			if (map[i][j]->bulletCollide(this->sprite, this->rotation, this->power)) {
				collide = true;
			}
		}
	}
	if (this->x < 4 || this->x > 204 || this->y < 4 || this->y > 204) return true;
	return collide;
}