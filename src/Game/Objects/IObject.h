#pragma once

#include <memory>
#include <vector>

#include "SFML/System.hpp"

#include "../Enums.h"
#include "../Event.h"
#include "../Game.h"

class IObject {
 public:
  IObject(ObjectType type, const sf::Vector2f& position, const sf::Vector2f& size);

  // Collision check
  bool operator|(const IObject& other) const;
  bool operator&(const IObject& other) const;

  uint16_t getId() const;
  ObjectType getType() const;
  sf::Vector2f getPosition() const;
  sf::Vector2f getSize() const;
  uint8_t getCollisionLayer() const;
  bool isDestroyed() const;
  virtual uint8_t getState() const;

  void setPosition(const sf::Vector2f& position);

  std::vector<std::shared_ptr<IObject>> getSoftCollisions(const std::vector<std::shared_ptr<IObject>>& objects) const;
  std::vector<std::shared_ptr<IObject>> getHardCollisions(const std::vector<std::shared_ptr<IObject>>& objects) const;

  virtual void think(Game& game, const Event &event);
  virtual void destroy(Game& game, const ObjectRotation& bulletRotation = ObjectRotation::Up);

 protected:
  uint16_t _id;
  ObjectType _type;

  sf::Vector2f _position;
  sf::Vector2f _size;

  bool _collision = true;
  uint8_t _collisionLayer = 0;
  bool _desytroyed = false;

 private:
  uint16_t generateId();
};
