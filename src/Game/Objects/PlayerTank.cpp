#include "PlayerTank.h"

PlayerTank::PlayerTank(const sf::Vector2f& position) : ITank(ObjectType::PlayerTank, position) {}


void PlayerTank::think(const std::vector<IObject> &objects, uint16_t index, const sf::Event& event) {

}
