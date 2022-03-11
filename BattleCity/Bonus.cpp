#include "Bonus.h"

Bonus::Bonus(const std::vector<std::vector<Block*>>& map, Tank* player1, Tank* player2, const std::vector<Tank*>& enemies) {
	this->type = std::rand() % 6;

	if (!this->texture.loadFromFile("resources/graphics/Bonuses.png", sf::IntRect(this->type << 4, 0, 16, 16))) throw 1;
	this->sprite.setScale(SCALE, SCALE);
	this->sprite.setTexture(this->texture);
	while (true) {
		bool collide = false;
		this->sprite.setPosition(std::rand() % 25 * SCALE << 3, std::rand() % 25 * SCALE << 3);
		for (uint8_t i = 0; i < map.size() && !collide; ++i) {
			for (uint8_t j = 0; j < map[i].size() && !collide; ++j) {
				if (map[i][j]->tankCollide(this->sprite)) {
					collide = true;
					break;
				}
				if (player1 != nullptr) {
					if (player1->spriteCollide(this->sprite, true)) {
						collide = true;
						break;
					}
				}
				if (player2 != nullptr) {
					if (player2->spriteCollide(this->sprite, true)) {
						collide = true;
						break;
					}
				}
				for (uint8_t i = 0; i < enemies.size(); ++i) {
					if (enemies[i]->spriteCollide(this->sprite, true)) {
						collide = true;
						break;
					}
				}
			}
		}
		if (!collide) break;
	}
	return;
}

bool Bonus::isTaken() {
	return this->taken;
}

void Bonus::collideCheck(Tank* player1, Tank* player2, const std::vector<Tank*>& enemies, const std::vector<std::vector<Block*>>& map, const sf::Clock& globalClock, float& playersFrozenUntil, float& enemiesFrozenUntil, std::vector<Explosion*>& explosions) {
	if (this->taken) return;
	if (player1 != nullptr) {
		if (player1->spriteCollide(this->sprite)) {
			if (this->type == BONUS_HELMET) {
				player1->helmet();
			}
			else if (this->type == BONUS_FREEZE) {
				enemiesFrozenUntil = globalClock.getElapsedTime().asSeconds() + FREEZE_TIME;
				for (uint8_t i = 0; i < enemies.size(); ++i) {
					enemies[i]->freeze();
				}
			}
			else if (this->type == BONUS_SHOWEL) {
				for (uint8_t i = 0; i < map.size(); ++i) {
					for (uint8_t j = 0; j < map[i].size(); ++j) {
						if (map[i][j]->getType() == BLOCK_PROTECTION) {
							map[i][j]->placeProtection();
						}
					}
				}
			}
			else if (this->type == BONUS_UPGRADE) {
				player1->levelUp();
			}
			else if (this->type == BONUS_GRANADE) {
				for (uint8_t i = 0; i < enemies.size(); ++i) {
					Explosion* exp = nullptr;
					enemies[i]->destroy(exp, true);
					if (exp != nullptr) {
						explosions.push_back(exp);
					}
				}
			}
			else if (this->type == BONUS_LIFE) {
				player1->addLife();
			}
			this->taken = true;
			return;
		}
	}
	if (player2 != nullptr) {
		if (player2->spriteCollide(this->sprite)) {
			if (this->type == BONUS_HELMET) {
				player2->helmet();
			}
			else if (this->type == BONUS_FREEZE) {
				enemiesFrozenUntil = globalClock.getElapsedTime().asSeconds() + FREEZE_TIME;
				for (uint8_t i = 0; i < enemies.size(); ++i) {
					enemies[i]->freeze();
				}
			}
			else if (this->type == BONUS_SHOWEL) {
				for (uint8_t i = 0; i < map.size(); ++i) {
					for (uint8_t j = 0; j < map[i].size(); ++j) {
						if (map[i][j]->getType() == BLOCK_PROTECTION) {
							map[i][j]->placeProtection();
						}
					}
				}
			}
			else if (this->type == BONUS_UPGRADE) {
				player2->levelUp();
			}
			else if (this->type == BONUS_GRANADE) {
				for (uint8_t i = 0; i < enemies.size(); ++i) {
					Explosion* exp = nullptr;
					enemies[i]->destroy(exp, true);
					if (exp != nullptr) {
						explosions.push_back(exp);
					}
				}
			}
			else if (this->type == BONUS_LIFE) {
				player2->addLife();
			}
			this->taken = true;
			return;
		}
	}
	for (uint8_t i = 0; i < enemies.size(); ++i) {
		if (enemies[i]->spriteCollide(this->sprite)) {
			if (this->type == BONUS_HELMET) {
				enemies[i]->helmet();
			}
			else if (this->type == BONUS_FREEZE) {
				playersFrozenUntil = globalClock.getElapsedTime().asSeconds() + FREEZE_TIME;
				if (player1 != nullptr) player1->freeze();
				if (player2 != nullptr) player2->freeze();
			}
			else if (this->type == BONUS_SHOWEL) {
				for (uint8_t i = 0; i < map.size(); ++i) {
					for (uint8_t j = 0; j < map[i].size(); ++j) {
						if (map[i][j]->getType() == BLOCK_PROTECTION) {
							map[i][j]->removeProtection();
						}
					}
				}
			}
			else if (this->type == BONUS_UPGRADE) {
				enemies[i]->levelUp();
			}
			else if (this->type == BONUS_GRANADE) {
				if (player1 != nullptr) {
					Explosion* exp = nullptr;
					player1->destroy(exp);
					if (exp != nullptr) {
						explosions.push_back(exp);
					}
				}
				if (player2 != nullptr) {
					Explosion* exp = nullptr;
					player2->destroy(exp);
					if (exp != nullptr) {
						explosions.push_back(exp);
					}
				}
			}
			else if (this->type == BONUS_LIFE) {
				enemies[i]->addLife();
			}
			this->taken = true;
			return;
		}
	}
	return;
}

void Bonus::draw(sf::RenderWindow& window) {
	if (this->taken) return;
	if (this->clock.getElapsedTime().asMilliseconds() % 300 < 150) window.draw(this->sprite);
	return;
}