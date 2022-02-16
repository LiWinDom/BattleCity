#include "Player.h"

Player::Player(const std::string& view, const uint8_t& x, const uint8_t& y, const uint8_t& level, const uint8_t& rotation) {
	this->view = view;
	this->startX = x;
	this->startY = y;
	this->level = level;
	this->startRotation = rotation;
	this->lives = 3;
	this->x = this->startX;
	this->y = this->startY;
	this->rotation = this->startRotation;

	for (uint8_t i = 0; i < 4; ++i) {
		for (uint8_t j = 0; j < 4; ++j) {
			if (!this->textures[i][j][0].loadFromFile("resources/graphics/" + this->view + ".png", sf::IntRect(j << 5, i << 4, 16, 16)) ||
				!this->textures[i][j][1].loadFromFile("resources/graphics/" + this->view + ".png", sf::IntRect((j << 5) + 16, i << 4, 16, 16))) throw 1;
		}
	}
	this->sprite.setOrigin(8, 8);
	this->sprite.setScale(SCALE, SCALE);
	this->sprite.setPosition(this->x * SCALE, this->y * SCALE);

	this->hitbox.setOrigin(8, 8);
	this->hitbox.setScale(SCALE, SCALE);
	this->hitbox.setTexture(this->textures[0][0][0]);
	this->hitbox.setPosition(this->x * SCALE, this->y * SCALE);

	return;
}

float Player::getSpeed() {
	return TANK_MEDIUM;
}

bool Player::isDestroyed() {
	return this->destroyed;
}

bool Player::spriteCollide(const sf::Sprite& sprite) {
	if (sprite.getPosition() == this->sprite.getPosition() || sprite.getPosition() == this->hitbox.getPosition()) return false;
	return sprite.getGlobalBounds().intersects(this->sprite.getGlobalBounds());
}

bool Player::bulletCollide(const std::vector<Bullet*>& bullets) {
	for (uint8_t i = 0; i < bullets.size(); ++i) {
		if (bullets[i]->spriteCollide(this->sprite)) {
			this->destroy();
			bullets[i]->destroy();
			return true;
		}
	}
	return false;
}

void Player::up(const std::vector<std::vector<Block*>>& map, const std::vector<Player*>& players) {
	this->rotation = TANK_UP;
	this->animation = !this->animation;
	this->sprite.setTexture(textures[this->level][this->rotation][this->animation]);

	// Changing hitbox pos
	uint8_t hitboxX = this->x - this->x % 4;
	uint8_t hitboxY = this->y - this->y % 4;
	if (this->x % 4 > 1) hitboxX += 4;
	if (this->y % 4 > 1) hitboxY += 4;

	// Changing pos
	--this->y;
	this->sprite.setPosition(this->x * SCALE, this->y * SCALE);
	if (blockCollide(map, this->sprite) || tankCollide(players, this->sprite)) {
		hitboxY -= 4;
		this->hitbox.setPosition(hitboxX * SCALE, hitboxY * SCALE);
		if (blockCollide(map, this->hitbox) || tankCollide(players, this->hitbox)) {
			++this->y;
			hitboxY += 4;
		}
		else {
			this->x = hitboxX;

			// Recalc
			uint8_t hitboxY = this->y - this->y % 4;
			if (this->y % 4 > 1) hitboxY += 4;
		}
	}
	this->sprite.setPosition(this->x * SCALE, this->y * SCALE);
	this->hitbox.setPosition(hitboxX * SCALE, hitboxY * SCALE);

	return;
}

void Player::left(const std::vector<std::vector<Block*>>& map, const std::vector<Player*>& players) {
	this->rotation = TANK_LEFT;
	this->animation = !this->animation;
	this->sprite.setTexture(textures[this->level][this->rotation][this->animation]);

	// Changing hitbox pos
	uint8_t hitboxX = this->x - this->x % 4;
	uint8_t hitboxY = this->y - this->y % 4;
	if (this->x % 4 > 1) hitboxX += 4;
	if (this->y % 4 > 1) hitboxY += 4;

	// Changing pos
	--this->x;
	this->sprite.setPosition(this->x * SCALE, this->y * SCALE);
	if (blockCollide(map, this->sprite)) {
		hitboxX -= 4;
		this->hitbox.setPosition(hitboxX * SCALE, hitboxY * SCALE);
		if (blockCollide(map, this->hitbox)) {
			++this->x;
			hitboxX += 4;
		}
		else {
			this->y = hitboxY;

			// Recalc
			uint8_t hitboxX = this->x - this->x % 4;
			if (this->x % 4 > 1) hitboxX += 4;
		}
	}
	this->sprite.setPosition(this->x * SCALE, this->y * SCALE);
	this->hitbox.setPosition(hitboxX * SCALE, hitboxY * SCALE);

	return;
}

void Player::down(const std::vector<std::vector<Block*>>& map, const std::vector<Player*>& players) {
	this->rotation = TANK_DOWN;
	this->animation = !this->animation;
	this->sprite.setTexture(textures[this->level][this->rotation][this->animation]);

	// Changing hitbox pos
	uint8_t hitboxX = this->x - this->x % 4;
	uint8_t hitboxY = this->y - this->y % 4;
	if (this->x % 4 > 1) hitboxX += 4;
	if (this->y % 4 > 1) hitboxY += 4;

	// Changing pos
	++this->y;
	this->sprite.setPosition(this->x * SCALE, this->y * SCALE);
	if (blockCollide(map, this->sprite)) {
		hitboxY += 4;
		this->hitbox.setPosition(hitboxX * SCALE, hitboxY * SCALE);
		if (blockCollide(map, this->hitbox)) {
			--this->y;
			hitboxY -= 4;
		}
		else {
			this->x = hitboxX;

			// Recalc
			uint8_t hitboxY = this->y - this->y % 4;
			if (this->y % 4 > 1) hitboxY += 4;
		}
	}
	this->sprite.setPosition(this->x * SCALE, this->y * SCALE);
	this->hitbox.setPosition(hitboxX * SCALE, hitboxY * SCALE);

	return;
}

void Player::right(const std::vector<std::vector<Block*>>& map, const std::vector<Player*>& players) {
	this->rotation = TANK_RIGHT;
	this->animation = !this->animation;
	this->sprite.setTexture(textures[this->level][this->rotation][this->animation]);

	// Changing hitbox pos
	uint8_t hitboxX = this->x - this->x % 4;
	uint8_t hitboxY = this->y - this->y % 4;
	if (this->x % 4 > 1) hitboxX += 4;
	if (this->y % 4 > 1) hitboxY += 4;

	// Changing pos
	++this->x;
	this->sprite.setPosition(this->x * SCALE, this->y * SCALE);
	if (blockCollide(map, this->sprite)) {
		hitboxX += 4;
		this->hitbox.setPosition(hitboxX * SCALE, hitboxY * SCALE);
		if (blockCollide(map, this->hitbox)) {
			--this->x;
			hitboxX -= 4;
		}
		else {
			this->y = hitboxY;

			// Recalc
			uint8_t hitboxX = this->x - this->x % 4;
			if (this->x % 4 > 1) hitboxX += 4;
		}
	}
	this->sprite.setPosition(this->x * SCALE, this->y * SCALE);
	this->hitbox.setPosition(hitboxX * SCALE, hitboxY * SCALE);

	return;
}

Bullet* Player::shoot() {
	// Too many bullets check
	if (bullets > 1 || (this->level < 2 && bullets > 0)) return nullptr;

	// Time check
	const float delay = this->level > 1 ? 0.125 : 0.25;
	if (clock.getElapsedTime().asSeconds() < lastShot + delay) return nullptr;

	Bullet* bullet;
	const uint8_t speed = this->level > 0 ? BULLET_FAST : BULLET_SLOW;
	const bool power = this->level == 3;
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

void Player::bulletDestroyed() {
	--this->bullets;
	return;
}

void Player::draw(sf::RenderWindow& window) {
	this->sprite.setTexture(this->textures[this->level][this->rotation][this->animation]);
	window.draw(sprite);
	return;
}

bool Player::blockCollide(const std::vector<std::vector<Block*>>& map, const sf::Sprite& sprite) {
	if (this->x < 8 || this->x > 200 || this->y < 8 || this->y > 200) return true;
	for (uint8_t i = 0; i < 26; ++i) {
		for (uint8_t j = 0; j < 26; ++j) {
			if (map[i][j]->tankCollide(sprite)) {
				return true;
			}
		}
	}
	return false;
}

bool Player::tankCollide(const std::vector<Player*>& players, const sf::Sprite& sprite) {
	for (uint8_t i = 0; i < players.size(); ++i) {
		if (players[i]->spriteCollide(sprite)) {
			return true;
		}
	}
	return false;
}

void Player::destroy() {
	--this->lives;
	this->destroyed = this->lives < 1;

	this->rotation = this->startRotation;
	this->x = this->startX;
	this->y = this->startY;
	this->sprite.setPosition(this->x * SCALE, this->y * SCALE);
	this->hitbox.setPosition(this->x * SCALE, this->y * SCALE);
	return;
}