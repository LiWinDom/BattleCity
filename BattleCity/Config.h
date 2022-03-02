#pragma once

// Global
#define DEBUG false
#define SCALE std::min(sf::VideoMode::getDesktopMode().width >> 8, sf::VideoMode::getDesktopMode().height >> 8)
#define NETWORK_PORT 61000

// Block
#define BLOCK_AIR 0
#define BLOCK_BRICK 'b'
#define BLOCK_WALL 'w'
#define BLOCK_BUSH 'B'
#define BLOCK_WATER 'W'
#define BLOCK_ICE 'i'
#define BLOCK_PROTECTION 'p'
#define BLOCK_EAGLE 'e'

// Tank
#define TANK_UP 0
#define TANK_LEFT 1
#define TANK_DOWN 2
#define TANK_RIGHT 3
#define TANK_PLAYER1 10
#define TANK_PLAYER2 11
#define TANK_ENEMY 12
#define TANK_WHITE 0
#define TANK_RED 1
#define TANK_YELLOW 2
#define TANK_GREEN 3
#define TANK_SLOW 30
#define TANK_MEDIUM 45
#define TANK_FAST 60
#define RESPAWN_TIME 1

// Bullet
#define BULLET_UP 0
#define BULLET_LEFT 1
#define BULLET_DOWN 2
#define BULLET_RIGHT 3
#define BULLET_PLAYER 4
#define BULLET_ENEMY 5
#define BULLET_SLOW 120
#define BULLET_FAST 240