#include "PlayerTank.h"

#include "Bullet.h"

PlayerTank::PlayerTank(const sf::Vector2f& position, const bool playerNum) : ITank(ObjectType::PlayerTank, position) {
  _hasBonus = playerNum;
}

void PlayerTank::think(std::vector<std::shared_ptr<IObject>> &objects, const sf::Clock& globalClock, const Event& event) {
  // Base think
  ITank::think(objects, globalClock, event);
}
