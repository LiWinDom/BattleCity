#include "Bullet.h"

Bullet::Bullet(const uint8_t& x, const uint8_t& y, const uint8_t& rotation, const float& speed, const float& power) {
	this->x = x;
	this->y = y;
	this->rotation = rotation;
	this->speed = speed;
	this->power = power;

	if (!this->texture.loadFromFile("resources/graphics/Bullets.png", sf::IntRect(this->rotation << 2, 0, 4, 4))) throw 1;
	this->sprite.setOrigin(2, 2);
	this->sprite.setScale(SCALE, SCALE);
	this->sprite.setPosition(this->x * SCALE, this->y * SCALE);
	this->sprite.setTexture(this->texture);

	lastMoveTime = clock.getElapsedTime().asSeconds();

	return;
}

bool Bullet::isDestroyed() {
	return this->destroyed;
}

void Bullet::destroy() {
	this->destroyed = true;
}

bool Bullet::spriteCollide(const sf::Sprite& sprite) {
	return sprite.getGlobalBounds().intersects(this->sprite.getGlobalBounds());
}

void Bullet::move(const std::vector<std::vector<Block*>>& map, const std::vector<Bullet*>& bullets, bool& gameOver) {
	while (this->clock.getElapsedTime().asSeconds() >= this->lastMoveTime + 1 / this->speed && !this->destroyed) {
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
		this->sprite.setPosition(this->x * SCALE, this->y * SCALE);
		bulletCollide(bullets);
		blockCollide(map, gameOver);
		this->lastMoveTime += 1 / this->speed;
	}
	return;
}

void Bullet::draw(sf::RenderWindow& window) {
	window.draw(sprite);
	return;
}

void Bullet::blockCollide(const std::vector<std::vector<Block*>>& map, bool& gameOver) {
	for (uint8_t i = 0; i < 26; ++i) {
		for (uint8_t j = 0; j < 26; ++j) {
			if (map[i][j]->bulletCollide(this->sprite, this->rotation, this->power, gameOver)) {
				this->destroy();
			}
		}
	}
	if (this->x < 4 || this->x > 204 || this->y < 4 || this->y > 204) this->destroy();
	return;
}

void Bullet::bulletCollide(const std::vector<Bullet*>& bullets) {
	for (uint8_t i = 0; i < bullets.size(); ++i) {
		if (bullets[i]->spriteCollide(this->sprite)) {
			this->destroy();
			bullets[i]->destroy();
		}
	}
}