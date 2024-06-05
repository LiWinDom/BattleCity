#ifndef BATTLECITY_OBJECT_H
#define BATTLECITY_OBJECT_H

#include <SFML/Graphics.hpp>
#include <vector>

enum class ObjectType {
  None = 0,
  Air = 1,
  Tank = 10,
  PlayerTank = 11,
  EnemyTank = 12,
};

class IObject {
 public:
  // Intersection check
  bool operator&(const IObject& other) {
    // TODO
    return false;
  }

  std::vector<sf::Sprite> getSprites() const;
  virtual sf::Vector2f getPosition() const;

  virtual void setPosition(const sf::Vector2f& position);

  virtual void think(const std::vector<IObject>& objects, uint16_t index) {};

 protected:
  sf::Texture _texture;
  std::vector<sf::Sprite> _sprites;
};


#endif // BATTLECITY_OBJECT_H
