#include "IObject.h"

IObject::IObject(ObjectType type, const sf::Vector2f& position, const sf::Vector2f& size) :
  _id(std::rand()), _type(type), _position(position), _size(size) {}

bool IObject::operator|(const IObject &other) const {
  if (!_collistion || !other._collistion) return false;

  return !(
      _position.x + _size.x <= other._position.x ||  // right side is left of other left side
      _position.x >= other._position.x + other._size.x ||  // left side is right of other right side
      _position.y + _size.y <= other._position.y ||  // bottom side is above other top side
      _position.y >= other._position.y + other._size.y  // top side is below other bottom side
  );
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

bool IObject::isDestroyed() const {
  return _desytroyed;
}

void IObject::setPosition(const sf::Vector2f &position) {
  _position = position;
}

std::vector<std::shared_ptr<IObject>> IObject::findIntersection(const std::vector<std::shared_ptr<IObject>>& objects) const {
  std::vector<std::shared_ptr<IObject>> intersects;

  for (const auto& object : objects) {
    if (_id == object->_id) {
      continue;
    }
    if (*this | *object) {
      intersects.push_back(object);
    }
  }
  return intersects;
};
