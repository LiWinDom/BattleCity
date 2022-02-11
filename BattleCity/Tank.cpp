#include "Tank.h"

Tank::Tank(const std::string& view, const uint8_t& x, const uint8_t& y, const uint8_t& level, const float& speed, const uint8_t& rotation) {
	this->view = view;
	this->x = x;
	this->y = y;
	this->level = level;
	this->speed = speed;
	this->rotation = rotation;

	for (uint8_t i = 0; i < 8; ++i) {
		for (uint8_t j = 0; j < 4; ++j) {
			if (!this->textures[i][j][0].loadFromFile("resources/graphics/" + this->view + ".png", sf::IntRect((j << 5) + 1, (i << 4) + 1, 14, 14)) ||
				!this->textures[i][j][1].loadFromFile("resources/graphics/" + this->view + ".png", sf::IntRect((j << 5) + 17, (i << 4) + 1, 14, 14))) throw 1;
		}
	}
	this->sprite.setOrigin(7, 7);
	this->sprite.setScale(4, 4);
	this->sprite.setPosition(this->x * 4, this->y * 4);

	return;
}

uint8_t Tank::getX() {
	return this->x;
}

uint8_t Tank::getY() {
	return this->y;
}

uint8_t Tank::getRotation() {
	return this->rotation;
}

float Tank::getSpeed() {
	return this->speed;
}

void Tank::up(const std::vector<std::vector<Block*>>& map) {
	this->rotation = TANK_UP;
	this->animation = !this->animation;
	this->sprite.setTexture(textures[this->level][this->rotation][this->animation]);

	// Changing pos
	--this->y;
	this->sprite.setPosition(this->x * 4, this->y * 4);
	if (blockCollide(map)) {
		++this->y;
		this->sprite.setPosition(this->x * 4, this->y * 4);
	}
	return;
}

void Tank::left(const std::vector<std::vector<Block*>>& map) {
	this->rotation = TANK_LEFT;
	this->animation = !this->animation;
	this->sprite.setTexture(textures[this->level][this->rotation][this->animation]);

	// Changing pos
	--this->x;
	this->sprite.setPosition(this->x * 4, this->y * 4);
	if (blockCollide(map)) {
		++this->x;
		this->sprite.setPosition(this->x * 4, this->y * 4);
	}
	return;
}

void Tank::down(const std::vector<std::vector<Block*>>& map) {
	this->rotation = TANK_DOWN;
	this->animation = !this->animation;
	this->sprite.setTexture(textures[this->level][this->rotation][this->animation]);

	// Changing pos
	++this->y;
	this->sprite.setPosition(this->x * 4, this->y * 4);
	if (blockCollide(map)) {
		--this->y;
		this->sprite.setPosition(this->x * 4, this->y * 4);
	}
	return;
}

void Tank::right(const std::vector<std::vector<Block*>>& map) {
	this->rotation = TANK_RIGHT;
	this->animation = !this->animation;
	this->sprite.setTexture(textures[this->level][this->rotation][this->animation]);

	// Changing pos
	++this->x;
	this->sprite.setPosition(this->x * 4, this->y * 4);
	if (blockCollide(map)) {
		--this->x;
		this->sprite.setPosition(this->x * 4, this->y * 4);
	}
	return;
}

void Tank::draw(sf::RenderWindow& window) {
	this->sprite.setTexture(this->textures[this->level][this->rotation][this->animation]);
	window.draw(sprite);
	return;
}

bool Tank::blockCollide(const std::vector<std::vector<Block*>>& map) {
	if (this->x < 8 || this->x > 200 || this->y < 8 || this->y > 200) return true;
	for (uint8_t i = 0; i < 26; ++i) {
		for (uint8_t j = 0; j < 26; ++j) {
			if (map[i][j]->tankCollide(this->sprite)) {
				return true;
			}
		}
	}
	return false;
}