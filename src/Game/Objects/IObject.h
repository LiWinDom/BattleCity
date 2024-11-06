#pragma once

#include <cstdint>
#include <memory>
#include <vector>

#include "SFML/System.hpp"

#include "../Event.h"

enum class ObjectType : uint8_t {
  None = 0,
  Air = 1,
  Brick = 2,
  Block = 3,
  Bush = 4,
  Water = 5,
  Tank = 10,
  PlayerTank = 11,
  EnemyTank = 12,
};

class IObject {
 public:
  IObject(ObjectType type, const sf::Vector2f& position, const sf::Vector2f& size);

  // Intersection check
  bool operator|(const IObject& other) const;

  ObjectType getType() const;
  sf::Vector2f getPosition() const;
  sf::Vector2f getSize() const;
  bool isDestroyed() const;
  virtual uint8_t getState() const = 0;

  void setPosition(const sf::Vector2f& position);

  std::vector<std::shared_ptr<IObject>> findCollisions(const std::vector<std::shared_ptr<IObject>>& objects) const;
  virtual void think(const std::vector<std::shared_ptr<IObject>>& objects, uint16_t index, const sf::Clock& globalClock, const Event& event) = 0;

 protected:
  uint16_t _id;
  ObjectType _type;

  sf::Vector2f _position;
  sf::Vector2f _size;

  bool _collistion = true;
  bool _desytroyed = false;
};
