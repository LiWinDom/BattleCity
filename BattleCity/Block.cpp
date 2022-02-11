#include "Block.h"

Block::Block(const uint8_t& view, const uint8_t& x, const uint8_t& y) {
	this->view = view;
	this->x = x;
	this->y = y;

	if (this->view == BLOCK_AIR) return;
	if (this->view == BLOCK_BRICK || this->view == BLOCK_PROTECTION) {
		if (!this->textures[0].loadFromFile("resources/graphics/Blocks.png", sf::IntRect(0, 0, 4, 4)) ||
			!this->textures[1].loadFromFile("resources/graphics/Blocks.png", sf::IntRect(4, 0, 4, 4))) throw 1;
		for (uint8_t i = 0; i < 4; ++i) {
			this->sprites[i].setTexture(this->textures[i == 1 || i == 2]);
			this->sprites[i].setScale(4, 4);
			this->sprites[i].setPosition((this->x * 2 + i % 2) << 4, (this->y * 2 + (i > 1)) << 4);
		}
	}
	else if (this->view == BLOCK_EAGLE) {
		if (!this->texture.loadFromFile("resources/graphics/Eagle.png", sf::IntRect(0, 0, 16, 16))) throw 1;
		this->sprite.setTexture(this->texture);
		this->sprite.setScale(4, 4);
		this->sprite.setPosition(this->x << 5, this->y << 5);
	}
	else {
		if (this->view == BLOCK_WALL) {
			if (!this->texture.loadFromFile("resources/graphics/Blocks.png", sf::IntRect(0, 4, 8, 8))) throw 1;
		}
		else if (this->view == BLOCK_BUSH) {
			if (!this->texture.loadFromFile("resources/graphics/Blocks.png", sf::IntRect(8, 4, 8, 8))) throw 1;
		}
		else if (this->view == BLOCK_ICE) {
			if (!this->texture.loadFromFile("resources/graphics/Blocks.png", sf::IntRect(16, 4, 8, 8))) throw 1;
		}
		this->sprite.setTexture(this->texture);
		this->sprite.setScale(4, 4);
		this->sprite.setPosition(this->x << 5, this->y << 5);
	}
	return;
}

void Block::draw(sf::RenderWindow& window) {
	if (this->view == BLOCK_AIR) return;
	if (this->view == BLOCK_BRICK || this->view == BLOCK_PROTECTION) {
		for (uint8_t i = 0; i < 4; ++i) {
			if (this->state[i]) {
				window.draw(this->sprites[i]);
			}
		}
	}
	else {
		window.draw(this->sprite);
	}
	return;
}

bool Block::tankCollide(const sf::Sprite& sprite) {
	if (this->view == BLOCK_AIR || this->view == BLOCK_BUSH || this->view == BLOCK_ICE) return false;
	if (this->view == BLOCK_BRICK || this->view == BLOCK_PROTECTION) {
		return (sprite.getGlobalBounds().intersects(this->sprites[0].getGlobalBounds()) && this->state[0]) ||
			(sprite.getGlobalBounds().intersects(this->sprites[1].getGlobalBounds()) && this->state[1]) ||
			(sprite.getGlobalBounds().intersects(this->sprites[2].getGlobalBounds()) && this->state[2]) ||
			(sprite.getGlobalBounds().intersects(this->sprites[3].getGlobalBounds()) && this->state[3]);
	}
	return sprite.getGlobalBounds().intersects(this->sprite.getGlobalBounds());
}

bool Block::bulletCollide(const sf::Sprite& sprite, const uint8_t& rotation, const bool& power) {
	if (this->view == BLOCK_AIR || this->view == BLOCK_BUSH || this->view == BLOCK_ICE || this->view == BLOCK_WATER) return false;
	if (this->view == BLOCK_BRICK || this->view == BLOCK_PROTECTION) {
		if (rotation == BULLET_UP) {
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
		else if (rotation == BULLET_LEFT) {
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
		else if (rotation == BULLET_DOWN) {
			if ((sprite.getGlobalBounds().intersects(this->sprites[0].getGlobalBounds()) && this->state[0]) ||
				(sprite.getGlobalBounds().intersects(this->sprites[1].getGlobalBounds()) && this->state[1])) {
				this->state[0] = false;
				this->state[1] = false;
				return true;
			}
			else if ((sprite.getGlobalBounds().intersects(this->sprites[2].getGlobalBounds()) && this->state[2]) ||
					(sprite.getGlobalBounds().intersects(this->sprites[3].getGlobalBounds()) && this->state[3])) {
				this->state[2] = false;
				this->state[3] = false;
				return true;
			}
		}
		else if (rotation == BULLET_RIGHT) {
			if ((sprite.getGlobalBounds().intersects(this->sprites[0].getGlobalBounds()) && this->state[0]) ||
				(sprite.getGlobalBounds().intersects(this->sprites[2].getGlobalBounds()) && this->state[2])) {
				this->state[0] = false;
				this->state[2] = false;
				return true;
			}
			else if ((sprite.getGlobalBounds().intersects(this->sprites[1].getGlobalBounds()) && this->state[1]) ||
					(sprite.getGlobalBounds().intersects(this->sprites[3].getGlobalBounds()) && this->state[3])) {
				this->state[1] = false;
				this->state[3] = false;
				return true;
			}
		}
	}
	else if (sprite.getGlobalBounds().intersects(this->sprite.getGlobalBounds())) {
		if (this->view == BLOCK_WALL && power) {
			this->view = BLOCK_AIR;
		}
		return true;
	}
	return false;
}