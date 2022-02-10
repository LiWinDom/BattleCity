#include "Tank.h"

Tank::Tank(const std::string& view, const uint8_t& x, const uint8_t& y, const uint8_t& level, const uint8_t& rotation) {
	this->view = view;
	this->x = x;
	this->y = y;
	this->level = level;
	this->rotation = rotation;

	for (uint8_t i = 0; i < 8; ++i) {
		for (uint8_t j = 0; j < 4; ++j) {
			if (!this->textures[i][j][0].loadFromFile("resources/graphics/" + this->view + ".png", sf::IntRect((j << 5) + 1, (i << 4) + 1, 14, 14)) ||
				!this->textures[i][j][1].loadFromFile("resources/graphics/" + this->view + ".png", sf::IntRect((j << 5) + 17, (i << 4) + 1, 14, 14))) {
				ShowWindow(GetConsoleWindow(), SW_SHOW);
				system("pause");
				throw 1;
			}
		}
	}
	this->sprite.setOrigin(7, 7);
	this->sprite.setScale(4, 4);

	return;
}

void Tank::set(const uint8_t& x, const uint8_t& y, const uint8_t& rotation, const bool& animation) {
	this->x = x;
	this->y = y;
	this->rotation = rotation;
	this->animation = animation;
	return;
}

void Tank::up(const std::vector<std::vector<Block*>>& map) {
	this->rotation = TANK_UP;
	this->animation = !this->animation;
	if (this->y <= 7) return;
	--this->y;
	this->sprite.setPosition(this->x * 4, this->y * 4);
	if (blockCollide(map)) {
		++this->y;
	}
	this->sprite.setPosition(this->x * 4, this->y * 4);
	return;
}

void Tank::left(const std::vector<std::vector<Block*>>& map) {
	this->rotation = TANK_LEFT;
	this->animation = !this->animation;
	if (this->x <= 7) return;
	--this->x;
	this->sprite.setPosition(this->x * 4, this->y * 4);
	if (blockCollide(map)) {
		++this->x;
	}
	this->sprite.setPosition(this->x * 4, this->y * 4);
	return;
}

void Tank::down(const std::vector<std::vector<Block*>>& map) {
	this->rotation = TANK_DOWN;
	this->animation = !this->animation;
	if (this->y >= 201) return;
	++this->y;
	this->sprite.setPosition(this->x * 4, this->y * 4);
	if (blockCollide(map)) {
		--this->y;
	}
	this->sprite.setPosition(this->x * 4, this->y * 4);
	return;
}

void Tank::right(const std::vector<std::vector<Block*>>& map) {
	this->rotation = TANK_RIGHT;
	this->animation = !this->animation;
	if (this->x >= 201) return;
	++this->x;
	this->sprite.setPosition(this->x * 4, this->y * 4);
	if (blockCollide(map)) {
		--this->x;
	}
	this->sprite.setPosition(this->x * 4, this->y * 4);
	return;
}

void Tank::draw(sf::RenderWindow& window) {
	this->sprite.setTexture(textures[this->level][this->rotation][this->animation]);
	this->sprite.setPosition(this->x * 4, this->y * 4);
	window.draw(sprite);
	return;
}

bool Tank::blockCollide(const std::vector<std::vector<Block*>>& map) {
	for (uint8_t i = 0; i < 26; ++i) {
		for (uint8_t j = 0; j < 26; ++j) {
			if (map[i][j]->tankCollide(this->sprite)) {
				return true;
			}
		}
	}
}