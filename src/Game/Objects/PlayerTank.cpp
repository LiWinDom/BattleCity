#include "PlayerTank.h"

#include "Bullet.h"

PlayerTank::PlayerTank(const sf::Vector2f& position, const bool playerNum) : ITank(ObjectType::PlayerTank, position) {
  _hasBonus = playerNum;
}

void PlayerTank::think(Game& game, const Event& event) {
  // Base think
  ITank::think(game, event);
}
