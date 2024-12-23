#include "IBlock.h"

IBlock::IBlock(ObjectType type, const sf::Vector2f& position) : IObject(type, position, sf::Vector2f(8, 8)) {}
