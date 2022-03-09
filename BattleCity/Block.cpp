#include "Block.h"

Block::Block(const uint8_t& type, const uint8_t& x, const uint8_t& y) {
	this->type = type;
	this->x = x;
	this->y = y;

	if (this->type == BLOCK_AIR) return;
	if (this->type == BLOCK_BRICK || this->type == BLOCK_PROTECTION) {
		if (!this->textures[0].loadFromFile("resources/graphics/Blocks.png", sf::IntRect(0, 0, 4, 4)) ||
			!this->textures[1].loadFromFile("resources/graphics/Blocks.png", sf::IntRect(4, 0, 4, 4))) throw 1;
		for (uint8_t i = 0; i < 4; ++i) {
			this->sprites[i].setTexture(this->textures[i == 1 || i == 2]);
			this->sprites[i].setScale(SCALE, SCALE);
			this->sprites[i].setPosition((this->x * 2 + i % 2) * (SCALE << 2), (this->y * 2 + (i > 1)) * (SCALE << 2));
		}
	}
	else if (this->type == BLOCK_EAGLE) {
		if (!this->textures[0].loadFromFile("resources/graphics/Eagle.png", sf::IntRect(0, 0, 16, 16)) ||
			!this->textures[1].loadFromFile("resources/graphics/Eagle.png", sf::IntRect(16, 0, 16, 16))) throw 1;
		this->sprite.setTexture(this->textures[0]);
		this->sprite.setScale(SCALE, SCALE);
		this->sprite.setPosition(this->x * (SCALE << 3), this->y * (SCALE << 3));
	}
	else if (this->type == BLOCK_WATER) {
		if (!this->textures[0].loadFromFile("resources/graphics/Blocks.png", sf::IntRect(8, 12, 8, 8)) ||
			!this->textures[1].loadFromFile("resources/graphics/Blocks.png", sf::IntRect(16, 12, 8, 8))) throw 1;

		this->sprite.setTexture(this->textures[0]);
		this->sprite.setScale(SCALE, SCALE);
		this->sprite.setPosition(this->x * (SCALE << 3), this->y * (SCALE << 3));
	}
	else {
		if (this->type == BLOCK_WALL) {
			if (!this->texture.loadFromFile("resources/graphics/Blocks.png", sf::IntRect(0, 4, 8, 8))) throw 1;
		}
		else if (this->type == BLOCK_BUSH) {
			if (!this->texture.loadFromFile("resources/graphics/Blocks.png", sf::IntRect(8, 4, 8, 8))) throw 1;
		}
		else if (this->type == BLOCK_ICE) {
			if (!this->texture.loadFromFile("resources/graphics/Blocks.png", sf::IntRect(16, 4, 8, 8))) throw 1;
		}
		this->sprite.setTexture(this->texture);
		this->sprite.setScale(SCALE, SCALE);
		this->sprite.setPosition(this->x * (SCALE << 3), this->y * (SCALE << 3));
	}
	return;
}

uint8_t Block::getType() {
	return this->type;
}

void Block::draw(sf::RenderWindow& window, const sf::Clock& clock) {
	if (this->type == BLOCK_AIR) return;
	if (this->type == BLOCK_BRICK || this->type == BLOCK_PROTECTION) {
		for (uint8_t i = 0; i < 4; ++i) {
			if (this->state[i]) {
				window.draw(this->sprites[i]);
			}
		}
	}
	else if (this->type == BLOCK_WATER) {
		this->sprite.setTexture(this->textures[clock.getElapsedTime().asMilliseconds() % 1000 < 500 ? 0 : 1]);
		window.draw(this->sprite);
	}
	else {
		window.draw(this->sprite);
	}
	return;
}

bool Block::tankCollide(const sf::Sprite& sprite) {
	if (this->type == BLOCK_AIR || this->type == BLOCK_BUSH || this->type == BLOCK_ICE) return false;
	if (this->type == BLOCK_BRICK || this->type == BLOCK_PROTECTION) {
		return (sprite.getGlobalBounds().intersects(this->sprites[0].getGlobalBounds()) && this->state[0]) ||
			(sprite.getGlobalBounds().intersects(this->sprites[1].getGlobalBounds()) && this->state[1]) ||
			(sprite.getGlobalBounds().intersects(this->sprites[2].getGlobalBounds()) && this->state[2]) ||
			(sprite.getGlobalBounds().intersects(this->sprites[3].getGlobalBounds()) && this->state[3]);
	}
	return sprite.getGlobalBounds().intersects(this->sprite.getGlobalBounds());
}

bool Block::bulletCollide(const sf::Sprite& sprite, const uint8_t& rotation, const bool& power, bool& eagleDestroyed) {
	if (this->type == BLOCK_AIR || this->type == BLOCK_BUSH || this->type == BLOCK_ICE || this->type == BLOCK_WATER) return false;
	if (this->type == BLOCK_BRICK || this->type == BLOCK_PROTECTION) {
		if (power) {
			if ((sprite.getGlobalBounds().intersects(this->sprites[0].getGlobalBounds()) && this->state[0]) ||
				(sprite.getGlobalBounds().intersects(this->sprites[1].getGlobalBounds()) && this->state[1]) ||
				(sprite.getGlobalBounds().intersects(this->sprites[2].getGlobalBounds()) && this->state[2]) ||
				(sprite.getGlobalBounds().intersects(this->sprites[3].getGlobalBounds()) && this->state[3])) {
				this->state[0] = false;
				this->state[1] = false;
				this->state[2] = false;
				this->state[3] = false;
				return true;
			}
		}
		else if (rotation == BULLET_UP || rotation == BULLET_DOWN) {
			if ((sprite.getGlobalBounds().intersects(this->sprites[2].getGlobalBounds()) && this->state[2]) ||
				(sprite.getGlobalBounds().intersects(this->sprites[3].getGlobalBounds()) && this->state[3])) {
				this->state[2] = false;
				this->state[3] = false;
				return true;
			}
			else if ((sprite.getGlobalBounds().intersects(this->sprites[0].getGlobalBounds()) && this->state[0]) ||
					(sprite.getGlobalBounds().intersects(this->sprites[1].getGlobalBounds()) && this->state[1])) {
				this->state[0] = false;
				this->state[1] = false;
				return true;
			}
		}
		else {
			if ((sprite.getGlobalBounds().intersects(this->sprites[1].getGlobalBounds()) && this->state[1]) ||
				(sprite.getGlobalBounds().intersects(this->sprites[3].getGlobalBounds()) && this->state[3])) {
				this->state[1] = false;
				this->state[3] = false;
				return true;
			}
			else if ((sprite.getGlobalBounds().intersects(this->sprites[0].getGlobalBounds()) && this->state[0]) ||
					(sprite.getGlobalBounds().intersects(this->sprites[2].getGlobalBounds()) && this->state[2])) {
				this->state[0] = false;
				this->state[2] = false;
				return true;
			}
		}
	}
	else if (sprite.getGlobalBounds().intersects(this->sprite.getGlobalBounds())) {
		if (this->type == BLOCK_WALL && power) {
			this->type = BLOCK_AIR;
		}
		else if (this->type == BLOCK_EAGLE) {
			this->sprite.setTexture(this->textures[1]);
			eagleDestroyed = true;
		}
		return true;
	}
	return false;
}