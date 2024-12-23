#include "Bush.h"

Bush::Bush(const sf::Vector2f& position) : IBlock(ObjectType::Bush, position) {
  _collision = false;
}
