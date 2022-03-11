#include "Tank.h"

Tank::Tank(const uint8_t& type, const uint8_t& x, const uint8_t& y, const uint8_t& level, const uint8_t& rotation, const float& freezeTime, const bool& bonus) {
	this->type = type;
	this->startX = x;
	this->startY = y;
	this->level = level;
	this->startRotation = rotation;
	this->frozenUntil = freezeTime;
	this->bonus = bonus;

	this->x = this->startX;
	this->y = this->startY;
	this->rotation = this->startRotation;

	// Loading textures
	if (this->type == TANK_PLAYER1) {
		for (uint8_t i = 0; i < 4; ++i) {
			for (uint8_t j = 0; j < 4; ++j) {
				if (!this->textures[i][j][0].loadFromFile("resources/graphics/TankYellow.png", sf::IntRect(j << 5, i << 4, 16, 16)) ||
					!this->textures[i][j][1].loadFromFile("resources/graphics/TankYellow.png", sf::IntRect((j << 5) + 16, i << 4, 16, 16))) throw 1;
			}
		}
		this->lives = 3;
		this->protectedUntil = 3;
	}
	else if (this->type == TANK_PLAYER2) {
		for (uint8_t i = 0; i < 4; ++i) {
			for (uint8_t j = 0; j < 4; ++j) {
				if (!this->textures[i][j][0].loadFromFile("resources/graphics/TankGreen.png", sf::IntRect(j << 5, i << 4, 16, 16)) ||
					!this->textures[i][j][1].loadFromFile("resources/graphics/TankGreen.png", sf::IntRect((j << 5) + 16, i << 4, 16, 16))) throw 1;
			}
		}
		this->lives = 3;
		this->protectedUntil = 3;
	}
	else {
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
		if (this->level == 3) {
			this->lives = 4;
		}
	}

	if (!this->protectionTextures[0].loadFromFile("resources/graphics/Protection.png", sf::IntRect(0, 0, 16, 16)) ||
		!this->protectionTextures[1].loadFromFile("resources/graphics/Protection.png", sf::IntRect(16, 0, 16, 16))) throw 1;
	for (uint8_t i = 0; i < 4; ++i) {
		if (!this->spawnFrames[i].loadFromFile("resources/graphics/Spawn.png", sf::IntRect(i << 4, 0, 16, 16))) throw 1;
	}
	for (uint8_t i = 0; i < 2; ++i) {
		if (!this->spawnFrames[i + 4].loadFromFile("resources/graphics/Spawn.png", sf::IntRect((2 - i) << 4, 0, 16, 16))) throw 1;
	}

	// Prepearing sprites
	this->sprite.setOrigin(8, 8);
	this->sprite.setScale(SCALE, SCALE);
	if (this->type == TANK_ENEMY) {
		this->sprite.setTexture(this->textures[this->color][this->rotation][this->animation]);
	}
	else {
		this->sprite.setTexture(this->textures[this->level][this->rotation][this->animation]);
	}
	this->sprite.setPosition(this->x * SCALE, this->y * SCALE);

	this->hitbox.setOrigin(8, 8);
	this->hitbox.setScale(SCALE, SCALE);
	this->hitbox.setTexture(this->textures[0][0][0]);
	this->hitbox.setPosition(this->x * SCALE, this->y * SCALE);

	this->protection.setOrigin(8, 8);
	this->protection.setScale(SCALE, SCALE);
	this->protection.setPosition(this->x * SCALE, this->y * SCALE);

	this->spawnSprite.setOrigin(8, 8);
	this->spawnSprite.setScale(SCALE, SCALE);
	this->spawnSprite.setPosition(this->startX * SCALE, this->startY * SCALE);

	this->destroyedTime = this->clock.getElapsedTime().asSeconds();
	if (this->type != TANK_ENEMY) {
		this->destroyedTime -= SPAWNING_TIME / 2.0;
	}

	return;
}

uint64_t Tank::getID() {
	return this->id;
}

bool Tank::isSpawned() {
	return this->spawned;
}

bool Tank::isDestroyed() {
	return this->destroyed;
}

float Tank::getSpeed() {
	if (this->type != TANK_ENEMY) {
		return TANK_MEDIUM;
	}
	if (this->type == 1) {
		return TANK_FAST;
	}
	return TANK_SLOW;
}

uint8_t Tank::getLives() {
	return this->lives;
}

bool Tank::getBonus() {
	return this->bonus;
}

void Tank::helmet() {
	this->protectedUntil = this->clock.getElapsedTime().asSeconds() + HELMET_TIME;
}

void Tank::freeze() {
	this->frozenUntil = this->clock.getElapsedTime().asSeconds() + FREEZE_TIME;
}

void Tank::levelUp() {
	this->level = std::min((uint8_t)(this->level + 1), (uint8_t)3);
	if (this->type == TANK_ENEMY) {
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
		if (this->level == 3) {
			this->lives = std::max(this->lives, (uint8_t)4);
		}
		return;
	}
	this->sprite.setTexture(textures[this->level][this->rotation][this->animation]);
	return;
}

void Tank::addLife() {
	++this->lives;
}

void Tank::spawn(Tank* player1, Tank* player2, const std::vector<Tank*>& enemies) {
	if (this->destroyedTime + SPAWNING_TIME > this->clock.getElapsedTime().asSeconds()) return;
	if (player1 != nullptr) {
		if (player1->getID() != this->id && player1->spriteCollide(this->spawnSprite)) return;
	}
	if (player2 != nullptr) {
		if (player2->getID() != this->id && player2->spriteCollide(this->spawnSprite)) return;
	}
	for (uint8_t i = 0; i < enemies.size(); ++i) {
		if (enemies[i]->getID() != this->id && enemies[i]->spriteCollide(this->spawnSprite)) return;
	}
	this->spawned = true;
	return;
}

bool Tank::spriteCollide(const sf::Sprite& sprite, const bool& countNotSpawned) {
	if ((!this->isSpawned() && !countNotSpawned) || this->isDestroyed()) return false;
	return this->hitbox.getGlobalBounds().intersects(sprite.getGlobalBounds()) || this->sprite.getGlobalBounds().intersects(sprite.getGlobalBounds());
}

bool Tank::bulletCollide(const std::vector<Bullet*>& bullets1, const std::vector<Bullet*>& bullets2) {
	if (!this->isSpawned() || this->isDestroyed()) return false;
	for (uint8_t i = 0; i < bullets1.size(); ++i) {
		if (bullets1[i]->spriteCollide(this->sprite)) {
			this->destroy();
			bullets1[i]->destroy();
			return true;
		}
	}
	for (uint8_t i = 0; i < bullets2.size(); ++i) {
		if (bullets2[i]->spriteCollide(this->sprite)) {
			bullets2[i]->destroy();
			if (this->type == TANK_ENEMY) {
				this->destroy();
			}
			else {
				this->frozenUntil = this->clock.getElapsedTime().asSeconds() + STUCK_TIME;
			}
			return true;
		}
	}
	return false;
}

bool Tank::bulletCollide(const std::vector<Bullet*>& bullets1, const std::vector<Bullet*>& bullets2, Explosion*& tankExplosion, Explosion*& bulletExplosion) {
	if (!this->isSpawned() || this->isDestroyed()) return false;
	for (uint8_t i = 0; i < bullets1.size(); ++i) {
		if (bullets1[i]->spriteCollide(this->sprite)) {
			this->destroy(tankExplosion);
			bullets1[i]->destroy(bulletExplosion);
			return true;
		}
	}
	for (uint8_t i = 0; i < bullets2.size(); ++i) {
		if (bullets2[i]->spriteCollide(this->sprite)) {
			bullets2[i]->destroy(bulletExplosion);
			if (this->type == TANK_ENEMY) {
				this->destroy(tankExplosion);
			}
			else {
				this->frozenUntil = this->clock.getElapsedTime().asSeconds() + STUCK_TIME;
			}
			return true;
		}
	}
	return false;
}

void Tank::up(const std::vector<std::vector<Block*>>& map, Tank* player1, Tank* player2, const std::vector<Tank*>& enemies) {
	if (!this->isSpawned() || this->isDestroyed() || this->frozenUntil > this->clock.getElapsedTime().asSeconds()) return;
	this->rotation = TANK_UP;
	this->animation = !this->animation;
	this->sprite.setTexture(textures[this->level][this->rotation][this->animation]);

	// Recalc hitbox pos
	uint8_t newX = this->x;
	uint8_t newY = this->y - 1;
	if (newX % 8 > 4) newX += 8;
	if (newY % 8 > 4) newY += 8;
	newX -= newX % 8;
	newY -= newY % 8;

	// Changing pos
	this->x = newX;
	this->hitbox.setPosition(newX * SCALE, newY * SCALE);
	if (this->blockCollide(map, this->hitbox) || this->tankCollide(player1, player2, enemies, this->hitbox)) {
		newY += 8;
	}
	else {
		--this->y;
		this->sprite.setPosition(this->x * SCALE, this->y * SCALE);
		if (this->blockCollide(map, this->sprite) || this->tankCollide(player1, player2, enemies, this->sprite)) {
			++this->y;
		}
	}
	this->sprite.setPosition(this->x * SCALE, this->y * SCALE);
	this->hitbox.setPosition(newX * SCALE, newY * SCALE);

	return;
}

void Tank::left(const std::vector<std::vector<Block*>>& map, Tank* player1, Tank* player2, const std::vector<Tank*>& enemies) {
	if (!this->isSpawned() || this->isDestroyed() || this->frozenUntil > this->clock.getElapsedTime().asSeconds()) return;
	this->rotation = TANK_LEFT;
	this->animation = !this->animation;
	this->sprite.setTexture(textures[this->level][this->rotation][this->animation]);

	// Recalc hitbox pos
	uint8_t newX = this->x - 1;
	uint8_t newY = this->y;
	if (newX % 8 > 4) newX += 8;
	if (newY % 8 > 4) newY += 8;
	newX -= newX % 8;
	newY -= newY % 8;

	// Changing pos
	this->y = newY;
	this->hitbox.setPosition(newX * SCALE, newY * SCALE);
	if (this->blockCollide(map, this->hitbox) || this->tankCollide(player1, player2, enemies, this->hitbox)) {
		newX += 8;
	}
	else {
		--this->x;
		this->sprite.setPosition(this->x * SCALE, this->y * SCALE);
		if (this->blockCollide(map, this->sprite) || this->tankCollide(player1, player2, enemies, this->sprite)) {
			++this->x;
		}
	}
	this->sprite.setPosition(this->x * SCALE, this->y * SCALE);
	this->hitbox.setPosition(newX * SCALE, newY * SCALE);

	return;
}

void Tank::down(const std::vector<std::vector<Block*>>& map, Tank* player1, Tank* player2, const std::vector<Tank*>& enemies) {
	if (!this->isSpawned() || this->isDestroyed() || this->frozenUntil > this->clock.getElapsedTime().asSeconds()) return;
	this->rotation = TANK_DOWN;
	this->animation = !this->animation;
	this->sprite.setTexture(textures[this->level][this->rotation][this->animation]);

	// Recalc hitbox pos
	uint8_t newX = this->x;
	uint8_t newY = this->y + 1;
	if (newX % 8 > 4) newX += 8;
	if (newY % 8 > 4) newY += 8;
	newX -= newX % 8;
	newY -= newY % 8;

	// Changing pos
	this->x = newX;
	this->hitbox.setPosition(newX * SCALE, newY * SCALE);
	if (this->blockCollide(map, this->hitbox) || this->tankCollide(player1, player2, enemies, this->hitbox)) {
		newY -= 8;
	}
	else {
		++this->y;
		this->sprite.setPosition(this->x * SCALE, this->y * SCALE);
		if (this->blockCollide(map, this->sprite) || this->tankCollide(player1, player2, enemies, this->sprite)) {
			--this->y;
		}
	}
	this->sprite.setPosition(this->x * SCALE, this->y * SCALE);
	this->hitbox.setPosition(newX * SCALE, newY * SCALE);

	return;
}

void Tank::right(const std::vector<std::vector<Block*>>& map, Tank* player1, Tank* player2, const std::vector<Tank*>& enemies) {
	if (!this->isSpawned() || this->isDestroyed() || this->frozenUntil > this->clock.getElapsedTime().asSeconds()) return;
	this->rotation = TANK_RIGHT;
	this->animation = !this->animation;
	this->sprite.setTexture(textures[this->level][this->rotation][this->animation]);

	// Recalc hitbox pos
	uint8_t newX = this->x + 1;
	uint8_t newY = this->y;
	if (newX % 8 > 4) newX += 8;
	if (newY % 8 > 4) newY += 8;
	newX -= newX % 8;
	newY -= newY % 8;

	// Changing pos
	this->y = newY;
	this->hitbox.setPosition(newX * SCALE, newY * SCALE);
	if (this->blockCollide(map, this->hitbox) || this->tankCollide(player1, player2, enemies, this->hitbox)) {
		newX -= 8;
	}
	else {
		++this->x;
		this->sprite.setPosition(this->x * SCALE, this->y * SCALE);
		if (this->blockCollide(map, this->sprite) || this->tankCollide(player1, player2, enemies, this->sprite)) {
			--this->x;
		}
	}
	this->sprite.setPosition(this->x * SCALE, this->y * SCALE);
	this->hitbox.setPosition(newX * SCALE, newY * SCALE);

	return;
}

void Tank::playerReset() {
	this->lives = std::max(this->lives, (uint8_t)3);
	this->spawned = false;
	this->destroyed = false;
	this->bullets = 0;

	this->x = this->startX;
	this->y = this->startY;
	this->rotation = this->startRotation;

	this->sprite.setTexture(textures[this->level][this->rotation][this->animation]);
	this->sprite.setPosition(this->x * SCALE, this->y * SCALE);
	this->hitbox.setPosition(this->x * SCALE, this->y * SCALE);

	this->destroyedTime = this->clock.getElapsedTime().asSeconds() - SPAWNING_TIME / 2.0;
	this->protectedUntil = this->clock.getElapsedTime().asSeconds() + SPAWN_PROTECTING_TIME;
	this->frozenUntil = -1;
}

Bullet* Tank::shoot() {
	if (!this->isSpawned() || this->isDestroyed() || this->frozenUntil > this->clock.getElapsedTime().asSeconds()) return nullptr;
	// Too many bullets check
	if (bullets > 1 || ((this->level < 2 || this->type == TANK_ENEMY) && bullets > 0)) return nullptr;

	// Time check
	const float delay = this->level > 1 && this->type != TANK_ENEMY ? 0.1 : 0.2;
	if (clock.getElapsedTime().asSeconds() < lastShot + delay) return nullptr;

	Bullet* bullet;
	const uint8_t speed = (this->level > 0 && this->type != TANK_ENEMY) || this->level == 2 ? BULLET_FAST : BULLET_SLOW;
	const bool power = this->level == 3 && this->type != TANK_ENEMY;
	if (this->rotation == TANK_UP) {
		bullet = new Bullet(this->x, this->y - 8, BULLET_UP, speed, power);
	}
	else if (this->rotation == TANK_LEFT) {
		bullet = new Bullet(this->x - 8, this->y, BULLET_LEFT, speed, power);
	}
	else if (this->rotation == TANK_DOWN) {
		bullet = new Bullet(this->x, this->y + 8, BULLET_DOWN, speed, power);
	}
	else {
		bullet = new Bullet(this->x + 8, this->y, BULLET_RIGHT, speed, power);
	}
	++this->bullets;
	this->lastShot = clock.getElapsedTime().asSeconds();
	return bullet;
}

void Tank::bulletDestroyed() {
	--this->bullets;
	return;
}

void Tank::draw(sf::RenderWindow& window) {
	if (this->isDestroyed() || (this->destroyedTime + SPAWNING_TIME / 2.0 > this->clock.getElapsedTime().asSeconds() && this->type != TANK_ENEMY)) return;
	if (!this->spawned) {
		uint8_t frame;
		if (this->type == TANK_ENEMY) {
			frame = (this->clock.getElapsedTime().asMilliseconds() / 100) % 6;
		}
		else {
			frame = (this->clock.getElapsedTime().asMilliseconds() / 60) % 6;
		}
		this->spawnSprite.setTexture(spawnFrames[frame]);
		window.draw(this->spawnSprite);
		return;
	}

	if (this->type == TANK_ENEMY) {
		changeColor();
		this->sprite.setTexture(textures[this->color][this->rotation][this->animation]);
	}
	window.draw(this->sprite);

	if (this->clock.getElapsedTime().asSeconds() < this->protectedUntil) {
		this->protection.setTexture(this->protectionTextures[this->clock.getElapsedTime().asMilliseconds() % 64 < 32 ? 0 : 1]);
		this->protection.setPosition(this->x * SCALE, this->y * SCALE);
		window.draw(this->protection);
	}
	return;
}

Bullet* Tank::think(const std::vector<std::vector<Block*>>& map, Tank* player1, Tank* player2, const std::vector<Tank*>& enemies) {
	if (!this->isSpawned() || this->isDestroyed() || this->frozenUntil > this->clock.getElapsedTime().asSeconds()) {
		this->lastMove = this->clock.getElapsedTime().asSeconds();
		return nullptr;
	}

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
		this->move(map, player1, player2, enemies);
	}
	else {
		bullet = this->move(map, player1, player2, enemies);
	}
	return bullet;
}

void Tank::destroy(const bool full) {
	if (this->clock.getElapsedTime().asSeconds() > this->protectedUntil && this->isSpawned()) {
		if (full) {
			this->lives = 0;
		}
		else {
			--this->lives;
		}
		this->destroyed = this->lives < 1;

		if (this->type != TANK_ENEMY) {
			this->x = this->startX;
			this->y = this->startY;
			this->rotation = this->startRotation;
			this->level = 0;
			this->spawned = false;
			this->destroyedTime = this->clock.getElapsedTime().asSeconds();

			this->sprite.setTexture(textures[this->level][this->rotation][this->animation]);
			this->sprite.setPosition(this->x * SCALE, this->y * SCALE);
			this->hitbox.setPosition(this->x * SCALE, this->y * SCALE);

			this->protectedUntil = this->clock.getElapsedTime().asSeconds() + SPAWN_PROTECTING_TIME;
		}
	}
	return;
}

void Tank::destroy(Explosion*& explosion, const bool full) {
	if (this->clock.getElapsedTime().asSeconds() > this->protectedUntil && this->isSpawned()) {
		if (full) {
			this->lives = 0;
		}
		else {
			--this->lives;
		}
		this->destroyed = this->lives < 1;

		if (this->type != TANK_ENEMY) {
			explosion = new Explosion(this->x, this->y, true);
			this->x = this->startX;
			this->y = this->startY;
			this->rotation = this->startRotation;
			this->level = 0;
			this->spawned = false;
			this->destroyedTime = this->clock.getElapsedTime().asSeconds();

			this->sprite.setTexture(textures[this->level][this->rotation][this->animation]);
			this->sprite.setPosition(this->x * SCALE, this->y * SCALE);
			this->hitbox.setPosition(this->x * SCALE, this->y * SCALE);

			this->protectedUntil = this->clock.getElapsedTime().asSeconds() + SPAWN_PROTECTING_TIME;
		}
		else if (this->destroyed) {
			explosion = new Explosion(this->x, this->y, true);
		}
	}
	return;
}

Bullet* Tank::move(const std::vector<std::vector<Block*>>& map, Tank* player1, Tank* player2, const std::vector<Tank*>& enemies) {
	Bullet* bullet = nullptr;

	if (this->isMove) {
		const float speed = this->level == 1 ? TANK_FAST : TANK_SLOW;
		while (clock.getElapsedTime().asSeconds() >= lastMove + 1 / speed) {
			this->animation = !this->animation;
			this->sprite.setTexture(textures[this->color][this->rotation][this->animation]);

			// Recalc hitbox pos
			uint8_t newX = this->x;
			uint8_t newY = this->y;
			if (this->rotation == TANK_UP) newY -= 1;
			else if (this->rotation == TANK_LEFT) newX -= 1;
			else if (this->rotation == TANK_DOWN) newY += 1;
			else newX += 1;
			if (newX % 8 > 4) newX += 8;
			if (newY % 8 > 4) newY += 8;
			newX -= newX % 8;
			newY -= newY % 8;

			// Changing pos
			if (this->rotation == TANK_UP || this->rotation == TANK_DOWN) this->x = newX;
			else this->y = newY;
			this->hitbox.setPosition(newX * SCALE, newY * SCALE);
			if (this->blockCollide(map, this->hitbox) || this->tankCollide(player1, player2, enemies, this->hitbox)) {
				if (this->rotation == TANK_UP) newY += 8;
				else if (this->rotation == TANK_LEFT) newX += 8;
				else if (this->rotation == TANK_DOWN) newY -= 8;
				else newX -= 8;

				const uint8_t action = std::rand() % 8;
				if (action == 0) {
					this->isMove = true;
					this->changeRotation();
				}
				else if (action < 2 && bullet == nullptr) {
					bullet = this->shoot();
				}
			}
			else {
				if (this->rotation == TANK_UP) --this->y;
				else if (this->rotation == TANK_LEFT) --this->x;
				else if (this->rotation == TANK_DOWN) ++this->y;
				else ++this->x;
				this->sprite.setPosition(this->x * SCALE, this->y * SCALE);
				if (this->blockCollide(map, this->sprite) || this->tankCollide(player1, player2, enemies, this->sprite)) {
					if (this->rotation == TANK_UP) ++this->y;
					else if (this->rotation == TANK_LEFT) ++this->x;
					else if (this->rotation == TANK_DOWN) --this->y;
					else --this->x;

					const uint8_t action = std::rand() % 8;
					if (action == 0) {
						this->isMove = true;
						this->changeRotation();
					}
					else if (action < 2 && bullet == nullptr) {
						bullet = this->shoot();
					}
				}
			}
			this->sprite.setPosition(this->x * SCALE, this->y * SCALE);
			this->hitbox.setPosition(newX * SCALE, newY * SCALE);
			lastMove += 1 / speed;
		}
	}
	else {
		lastMove = clock.getElapsedTime().asSeconds();
	}
	return bullet;
}

void Tank::changeRotation() {
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

void Tank::changeColor() {
	if (this->bonus && this->clock.getElapsedTime().asMilliseconds() % 300 < 150) {
		this->color = TANK_RED;
		return;
	}
	if (this->lives > 4) {
		if (this->color == TANK_WHITE) this->color = TANK_RED;
		else this->color = TANK_WHITE;
		return;
	}
	if (this->lives == 4) {
		if (this->color == TANK_WHITE) this->color = TANK_GREEN;
		else this->color = TANK_WHITE;
		return;
	}
	if (this->lives == 3) {
		if (this->color == TANK_WHITE) this->color = TANK_YELLOW;
		else this->color = TANK_WHITE;
		return;
	}
	if (this->lives == 2) {
		if (this->color == TANK_YELLOW) this->color = TANK_GREEN;
		else this->color = TANK_YELLOW;
		return;
	}
	this->color = TANK_WHITE;
	return;
}

bool Tank::blockCollide(const std::vector<std::vector<Block*>>& map, const sf::Sprite& sprite) {
	if (!this->isSpawned() || this->isDestroyed()) return false;
	if (this->x < 8 || this->x > 200 || this->y < 8 || this->y > 200) return true;
	for (uint8_t i = 0; i < 26; ++i) {
		for (uint8_t j = 0; j < 26; ++j) {
			if (map[i][j]->tankCollide(sprite)) return true;
		}
	}
	return false;
}

bool Tank::tankCollide(Tank* player1, Tank* player2, const std::vector<Tank*>& enemies, const sf::Sprite& sprite) {
	if (!this->isSpawned() || this->isDestroyed()) return false;
	if (player1 != nullptr) {
		if (player1->getID() != this->id) {
			if (player1->spriteCollide(sprite)) return true;
		}
	}
	if (player2 != nullptr) {
		if (player2->getID() != this->id) {
			if (player2->spriteCollide(sprite)) return true;
		}
	}
	for (uint8_t i = 0; i < enemies.size(); ++i) {
		if (enemies[i]->getID() == this->id) continue;
		if (enemies[i]->spriteCollide(sprite)) return true;
	}
	return false;
}