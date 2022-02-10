#include "Block.h"

Block::Block(const uint8_t& view, const uint8_t& x, const uint8_t& y) {
	this->view = view;
	this->x = x;
	this->y = y;

	if (this->view == BLOCK_AIR) return;
	if (this->view == BLOCK_BRICK) {
		if (!this->textures[0].loadFromFile("resources/graphics/Blocks.png", sf::IntRect(0, 0, 4, 4)) ||
			!this->textures[1].loadFromFile("resources/graphics/Blocks.png", sf::IntRect(4, 0, 4, 4))) {
			ShowWindow(GetConsoleWindow(), SW_SHOW);
			system("pause");
			throw 1;
		}
		for (uint8_t i = 0; i < 4; ++i) {
			this->sprites[i].setTexture(textures[i == 1 || i == 2]);
			this->sprites[i].setScale(4, 4);
			this->sprites[i].setPosition((this->x * 2 + i % 2) << 4, (this->y * 2 + (i > 1)) << 4);
		}
	}
	else {
		if (this->view == BLOCK_WALL) {
			if (!this->texture.loadFromFile("resources/graphics/Blocks.png", sf::IntRect(0, 4, 8, 8))) {
				ShowWindow(GetConsoleWindow(), SW_SHOW);
				system("pause");
				throw 1;
			}
		}
		else if (this->view == BLOCK_BUSH) {
			if (!this->texture.loadFromFile("resources/graphics/Blocks.png", sf::IntRect(8, 4, 8, 8))) {
				ShowWindow(GetConsoleWindow(), SW_SHOW);
				system("pause");
				throw 1;
			}
		}
		else if (this->view == BLOCK_ICE) {
			if (!this->texture.loadFromFile("resources/graphics/Blocks.png", sf::IntRect(16, 4, 8, 8))) {
				ShowWindow(GetConsoleWindow(), SW_SHOW);
				system("pause");
				throw 1;
			}
		}
		this->sprite.setTexture(texture);
		this->sprite.setScale(4, 4);
		this->sprite.setPosition(this->x << 5, this->y << 5);
	}
	return;
}

void Block::draw(sf::RenderWindow& window) {
	if (this->view == BLOCK_AIR) return;
	if (this->view == BLOCK_BRICK) {
		for (uint8_t i = 0; i < 4; ++i) {
			window.draw(sprites[i]);
		}
	}
	else {
		window.draw(sprite);
	}
	return;
}

bool Block::tankCollide(const sf::Sprite& sprite) {
	if (this->view == BLOCK_AIR) return false;
	if (this->view == BLOCK_BUSH) return false;
	if (this->view == BLOCK_BRICK) {
		return sprite.getGlobalBounds().intersects(this->sprites[0].getGlobalBounds()) ||
			sprite.getGlobalBounds().intersects(this->sprites[1].getGlobalBounds()) ||
			sprite.getGlobalBounds().intersects(this->sprites[2].getGlobalBounds()) ||
			sprite.getGlobalBounds().intersects(this->sprites[3].getGlobalBounds());
	}
	return sprite.getGlobalBounds().intersects(this->sprite.getGlobalBounds());
}