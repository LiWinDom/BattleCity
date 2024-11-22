#include "PlayerTank.h"

#include "Bullet.h"

PlayerTank::PlayerTank(const sf::Vector2f& position) : ITank(ObjectType::PlayerTank, position) {}

void PlayerTank::think(std::vector<std::shared_ptr<IObject>> &objects, const sf::Clock& globalClock, const Event& event) {
  // Base think
  ITank::think(objects, globalClock, event);
}
