#include "Explosion.h"

Explosion::Explosion(const uint8_t& x, const uint8_t& y, const bool& big) {
	this->x = x;
	this->y = y;
	this->big = big;

	if (this->big) {
		for (uint8_t i = 0; i < 5; ++i) {
			if (!this->frames[i].loadFromFile("resources/graphics/Explosion.png", sf::IntRect(i << 5, 0, 32, 32))) throw 1;
		}
		for (uint8_t i = 0; i < 4; ++i) {
			if (!this->frames[i + 5].loadFromFile("resources/graphics/Explosion.png", sf::IntRect((3 - i) << 5, 0, 32, 32))) throw 1;
		}
	}
	else {
		for (uint8_t i = 0; i < 3; ++i) {
			if (!this->frames[i].loadFromFile("resources/graphics/Explosion.png", sf::IntRect(i << 5, 0, 32, 32))) throw 1;
		}
		for (uint8_t i = 0; i < 2; ++i) {
			if (!this->frames[i + 3].loadFromFile("resources/graphics/Explosion.png", sf::IntRect((1 - i) << 5, 0, 32, 32))) throw 1;
		}
	}
	this->sprite.setTexture(this->frames[this->frame]);
	this->sprite.setOrigin(16, 16);
	this->sprite.setScale(SCALE, SCALE);
	this->sprite.setPosition(this->x * SCALE, this->y * SCALE);

	return;
}

bool Explosion::isEnded() {
	return this->frame > 8 || (this->frame > 4 && !this->big);
}

void Explosion::draw(sf::RenderWindow& window) {
	if (this->frame > 8 || (this->frame > 4 && !this->big)) return;

	while (this->clock.getElapsedTime().asSeconds() > this->lastChange + 0.05) {
		++this->frame;
		this->lastChange += 0.05;
		this->sprite.setTexture(frames[this->frame]);
		if (this->frame > 8 || (this->frame > 4 && !this->big)) return;
	}
	window.draw(this->sprite);

	return;
}