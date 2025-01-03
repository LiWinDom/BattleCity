#include "IObject.h"

IObject::IObject(ObjectType type, const sf::Vector2f& position, const sf::Vector2f& size) :
  _id(generateId()), _type(type), _position(position), _size(size) {}

uint16_t IObject::generateId() {
  static uint16_t prevId = 0;
  return prevId++;
}

bool IObject::operator|(const IObject &other) const {
  if (_desytroyed || other._desytroyed) return false;
  if (!_collision || !other._collision) return false;

  return !(
      _position.x + _size.x <= other._position.x ||  // right side is left of other left side
      _position.x >= other._position.x + other._size.x ||  // left side is right of other right side
      _position.y + _size.y <= other._position.y ||  // bottom side is above other top side
      _position.y >= other._position.y + other._size.y  // top side is below other bottom side
  );
}

bool IObject::operator&(const IObject &other) const {
  if (_collisionLayer < other._collisionLayer) return false;

  return operator|(other);
}

uint16_t IObject::getId() const {
  return _id;
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

uint8_t IObject::getState() const {
  return 0;
}

void IObject::setPosition(const sf::Vector2f &position) {
  _position = position;
}

std::vector<std::shared_ptr<IObject>> IObject::getSoftCollisions(const std::vector<std::shared_ptr<IObject>>& objects) const {
  std::vector<std::shared_ptr<IObject>> colliders;

  for (const auto& object : objects) {
    if (_id == object->_id) {
      continue;
    }
    if (*this | *object) {
      colliders.push_back(object);
    }
  }
  return colliders;
};

std::vector<std::shared_ptr<IObject>> IObject::getHardCollisions(const std::vector<std::shared_ptr<IObject>>& objects) const {
  std::vector<std::shared_ptr<IObject>> colliders;

  for (const auto& object : objects) {
    if (_id == object->_id) {
      continue;
    }
    if (*this & *object) {
      colliders.push_back(object);
    }
  }
  return colliders;
};

void IObject::think(Game& game, const Event &event) {
  return;
}

void IObject::destroy(Game& game, const ObjectRotation bulletRotation) {
  return;
}
