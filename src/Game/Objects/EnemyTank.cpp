#include "EnemyTank.h"

#include "Bullet.h"

EnemyTank::EnemyTank(const sf::Vector2f& position, const bool playerNum) : ITank(ObjectType::EnemyTank, position) {
  _hasBonus = playerNum;
}

void EnemyTank::think(Game& game, const Event& event) {
  // Base think
  Event newEvent;
  newEvent.player1.up = std::rand() % 2 == 0;
  newEvent.player1.left = std::rand() % 2 == 0;
  newEvent.player1.down = std::rand() % 2 == 0;
  newEvent.player1.right = std::rand() % 2 == 0;
  newEvent.player1.shoot = std::rand() % 16 == 0;
  ITank::think(game, newEvent);
}
