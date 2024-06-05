#ifndef BATTLECITY_OBJECT_H
#define BATTLECITY_OBJECT_H

#include <SFML/System.hpp>
#include <stdint.h>
#include <vector>

enum class ObjectType : uint8_t {
  None = 0,
  Air = 1,
  Tank = 10,
  PlayerTank = 11,
  EnemyTank = 12,
};

class IObject {
 public:
  IObject(ObjectType type = ObjectType::None);

  // Intersection check
  bool operator&(const IObject& other);

  ObjectType getType();
  sf::Vector2f getPosition() const;
  sf::Vector2f getSize();

  void setPosition(const sf::Vector2f& position);

  virtual void think(const std::vector<IObject>& objects, uint16_t index) {};

 protected:
  ObjectType _type;

  sf::Vector2f _position;
  sf::Vector2f _size;
};


#endif // BATTLECITY_OBJECT_H
