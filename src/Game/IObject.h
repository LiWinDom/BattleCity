#ifndef BATTLECITY_IOBJECT_H
#define BATTLECITY_IOBJECT_H

#include <cstdint>
#include <memory>
#include <SFML/System.hpp>
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
  IObject(ObjectType type, const sf::Vector2f& position, const sf::Vector2f& size);

  // Intersection check
  bool operator&(const IObject& other);

  ObjectType getType() const;
  sf::Vector2f getPosition() const;
  sf::Vector2f getSize() const;
  virtual uint16_t getState() const = 0;

  void setPosition(const sf::Vector2f& position);

  virtual void think(const std::vector<std::shared_ptr<IObject>>& objects, uint16_t index, const sf::Clock& globalClock) = 0;

 protected:
  ObjectType _type;

  sf::Vector2f _position;
  sf::Vector2f _size;
};


#endif // BATTLECITY_IOBJECT_H
