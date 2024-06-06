#include "IObject.h"

IObject::IObject(ObjectType type, const sf::Vector2f& position, const sf::Vector2f& size) :
  _type(type), _position(position), _size(size) {}

bool IObject::operator&(const IObject &other) {
  sf::Vector2f pos2 = _position + _size, pos4 = other._position + other._size;
  if (_position.x < other._position.x) {
    if (other._position.x > pos2.x) return false;
  }
  else {
    if (_position.x < pos4.x) return false;
  }
  if (_position.y < other._position.y) {
    if (other._position.y > pos2.y) return false;
  }
  else {
    if (_position.y < pos4.y) return false;
  }
  return true;
}

ObjectType IObject::getType() const {
  return _type;
}

sf::Vector2f IObject::getPosition() const {
  return _position;
}

sf::Vector2f IObject::getSize() const {
  return _size;
}

void IObject::setPosition(const sf::Vector2f &position) {
  _position = position;
}