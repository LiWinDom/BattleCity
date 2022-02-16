#include "Enemy.h"

Enemy::Enemy(const uint8_t& x, const uint8_t& y, const uint8_t& level, const uint8_t& rotation, const bool& bonus) {
	this->x = x;
	this->y = y;
	this->level = level;
	this->rotation = rotation;
	this->bonus = bonus;
	this->lives = this->level == 3 ? 4 : 1;

	for (uint8_t i = 0; i < 4; ++i) {
		if (!this->textures[0][i][0].loadFromFile("resources/graphics/TankWhite.png", sf::IntRect(i << 5, (this->level + 4) << 4, 16, 16)) ||
			!this->textures[0][i][1].loadFromFile("resources/graphics/TankWhite.png", sf::IntRect((i << 5) + 16, (this->level + 4) << 4, 16, 16))) throw 1;
		if (!this->textures[1][i][0].loadFromFile("resources/graphics/TankRed.png", sf::IntRect(i << 5, (this->level + 4) << 4, 16, 16)) ||
			!this->textures[1][i][1].loadFromFile("resources/graphics/TankRed.png", sf::IntRect((i << 5) + 16, (this->level + 4) << 4, 16, 16))) throw 1;
		if (!this->textures[2][i][0].loadFromFile("resources/graphics/TankYellow.png", sf::IntRect(i << 5, (this->level + 4) << 4, 16, 16)) ||
			!this->textures[2][i][1].loadFromFile("resources/graphics/TankYellow.png", sf::IntRect((i << 5) + 16, (this->level + 4) << 4, 16, 16))) throw 1;
		if (!this->textures[3][i][0].loadFromFile("resources/graphics/TankGreen.png", sf::IntRect(i << 5, (this->level + 4) << 4, 16, 16)) ||
			!this->textures[3][i][1].loadFromFile("resources/graphics/TankGreen.png", sf::IntRect((i << 5) + 16, (this->level + 4) << 4, 16, 16))) throw 1;
	}
	this->sprite.setOrigin(8, 8);
	this->sprite.setScale(SCALE, SCALE);
	this->sprite.setPosition(this->x * SCALE, this->y * SCALE);

	this->hitbox.setOrigin(8, 8);
	this->hitbox.setScale(SCALE, SCALE);
	this->hitbox.setTexture(this->textures[0][0][0]);
	this->hitbox.setPosition(this->x * SCALE, this->y * SCALE);

	std::srand(std::time(nullptr));
	lastMove = clock.getElapsedTime().asSeconds();

	return;
}

bool Enemy::isDestroyed() {
	return this->destroyed;
}

bool Enemy::spriteCollide(const sf::Sprite& sprite) {
	if (sprite.getPosition() == this->sprite.getPosition() || sprite.getPosition() == this->hitbox.getPosition()) return false;
	return sprite.getGlobalBounds().intersects(this->sprite.getGlobalBounds());
}

void Enemy::bulletCollide(const std::vector<Bullet*>& bullets) {
	for (uint8_t i = 0; i < bullets.size(); ++i) {
		if (bullets[i]->spriteCollide(this->sprite)) {
			this->destroy();
			bullets[i]->destroy();
		}
	}
	return;
}

Bullet* Enemy::think(const std::vector<std::vector<Block*>>& map, const std::vector<Player*>& players, const std::vector<Enemy*>& enemies) {
	if (this->isDestroyed()) return nullptr;

	const uint8_t action = std::rand() % 192;
	Bullet* bullet = nullptr;

	if (action < 2) {
		bullet = this->shoot();
	}
	else if (action == 2 || (action < 4 && isMove == false)) {
		const uint8_t action = std::rand() % 16;
		if (action == 0) {
			this->isMove = false;
		}
		else {
			this->isMove = true;
			changeRotation();
		}
	}

	if (bullet != nullptr) {
		this->move(map, players, enemies);
	}
	else {
		bullet = this->move(map, players, enemies);
	}

	return bullet;
}

void Enemy::bulletDestroyed() {
	--this->bullets;
	return;
}

void Enemy::draw(sf::RenderWindow& window) {
	changeColor();
	this->sprite.setTexture(this->textures[this->color][this->rotation][this->animation]);
	window.draw(sprite);
	return;
}

Bullet* Enemy::move(const std::vector<std::vector<Block*>>& map, const std::vector<Player*>& players, const std::vector<Enemy*>& enemies) {
	Bullet* bullet = nullptr;

	if (this->isMove) {
		const float speed = this->level == 1 ? TANK_FAST : TANK_SLOW;
		while (clock.getElapsedTime().asSeconds() >= lastMove + 1 / speed) {
			this->animation = !this->animation;
			this->sprite.setTexture(textures[this->level][this->rotation][this->animation]);

			// Changing hitbox pos
			uint8_t hitboxX = this->x - this->x % 4;
			uint8_t hitboxY = this->y - this->y % 4;
			if (this->x % 4 > 1) hitboxX += 4;
			if (this->y % 4 > 1) hitboxY += 4;

			// Changing pos
			if (this->rotation == TANK_UP) --this->y;
			else if (this->rotation == TANK_LEFT) --this->x;
			else if (this->rotation == TANK_DOWN) ++this->y;
			else ++this->x;
			this->sprite.setPosition(this->x * SCALE, this->y * SCALE);

			if (blockCollide(map, this->sprite) || tankCollide(players, enemies, this->sprite)) {
				if (this->rotation == TANK_UP) hitboxY -= 4;
				else if (this->rotation == TANK_LEFT) hitboxX -= 4;
				else if (this->rotation == TANK_DOWN) hitboxY += 4;
				else hitboxX += 4;
				this->hitbox.setPosition(hitboxX * SCALE, hitboxY * SCALE);

				if (blockCollide(map, this->hitbox) || tankCollide(players, enemies, this->hitbox)) {
					if (this->rotation == TANK_UP) {
						++this->y;
						hitboxY += 4;
					}
					else if (this->rotation == TANK_LEFT) {
						++this->x;
						hitboxX += 4;
					}
					else if (this->rotation == TANK_DOWN) {
						--this->y;
						hitboxY -= 4;
					}
					else {
						--this->x;
						hitboxX -= 4;
					}

					const uint8_t action = std::rand() % 8;
					if (action == 0) {
						this->isMove = true;
						changeRotation();
					}
					else if (action < 2 && bullet == nullptr) {
						bullet = this->shoot();
					}
				}
				else {
					if (this->rotation == TANK_UP || this->rotation == TANK_DOWN) this->x = hitboxX;
					else this->x = hitboxX;

					// Recalc
					uint8_t hitboxX = this->x - this->x % 4;
					uint8_t hitboxY = this->y - this->y % 4;
					if (this->x % 4 > 1) hitboxX += 4;
					if (this->y % 4 > 1) hitboxY += 4;
				}
			}
			this->sprite.setPosition(this->x * SCALE, this->y * SCALE);
			this->hitbox.setPosition(hitboxX * SCALE, hitboxY * SCALE);
			lastMove += 1 / speed;
		}
	}
	else {
		lastMove = clock.getElapsedTime().asSeconds();
	}
	return bullet;
}

void Enemy::changeRotation() {
	const bool smart = std::rand() % 2;
	if (smart) {
		if (std::rand() % 2) {
			this->rotation = (this->rotation + 1) % 4;
		}
		else {
			this->rotation = (this->rotation + 3) % 4;
		}
	}
	else {
		this->rotation = std::rand() % 4;
	}
	return;
}

Bullet* Enemy::shoot() {
	// Too many bullets check
	if (bullets > 0) return nullptr;

	// Time check
	if (clock.getElapsedTime().asSeconds() < lastShot + 0.25) return nullptr;

	Bullet* bullet;
	const uint8_t speed = this->level == 2 ? BULLET_FAST : BULLET_SLOW;
	if (this->rotation == TANK_UP) {
		bullet = new Bullet(this->x, this->y - 8, BULLET_UP, speed);
	}
	else if (this->rotation == TANK_LEFT) {
		bullet = new Bullet(this->x - 8, this->y, BULLET_LEFT, speed);
	}
	else if (this->rotation == TANK_DOWN) {
		bullet = new Bullet(this->x, this->y + 8, BULLET_DOWN, speed);
	}
	else {
		bullet = new Bullet(this->x + 8, this->y, BULLET_RIGHT, speed);
	}
	++this->bullets;
	this->lastShot = clock.getElapsedTime().asSeconds();
	return bullet;
}

bool Enemy::blockCollide(const std::vector<std::vector<Block*>>& map, const sf::Sprite& sprite) {
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

bool Enemy::tankCollide(const std::vector<Player*>& players, const std::vector<Enemy*>& enemies, const sf::Sprite& sprite) {
	for (uint8_t i = 0; i < players.size(); ++i) {
		if (players[i]->spriteCollide(sprite)) {
			return true;
		}
	}
	for (uint8_t i = 0; i < enemies.size(); ++i) {
		if (enemies[i]->spriteCollide(sprite)) {
			return true;
		}
	}
	return false;
}

void Enemy::destroy() {
	--this->lives;
	this->destroyed = this->lives < 1;
	this->bonus = false;
	return;
}

void Enemy::changeColor() {
	if (this->bonus) {
		if (this->color == 0) this->color = 1;
		else this->color = 0;
	}
	if (this->level == 3) {
		if (this->lives == 4) {
			if (this->color == 0) this->color = 3;
			else this->color = 0;
		}
		else if (this->lives == 3) {
			if (this->color == 0) this->color = 2;
			else this->color = 0;
		}
		else if (this->lives == 2) {
			if (this->color == 2) this->color = 3;
			else this->color = 2;
		}
		else {
			this->color = 0;
		}
	}
	return;
}