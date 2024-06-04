#pragma once
#ifndef BATTLECITY_OBJECT_H
#define BATTLECITY_OBJECT_H

#include <SFML/Graphics.hpp>
#include <vector>

enum class ObjectType {
  None = 0,
  Block = 1,
  Tank = 2,
};

class IObject {
 public:
  IObject(const sf::Vector2f& position, const sf::Vector2u& size, ObjectType type);


  //sf::Vector2i getPosition() const { return _position; }

  //sf::Vector2u getSize() const { return _size; }

  std::vector<sf::Sprite> getSprites() const { return _sprites; }

  //void setPosition(const sf::Vector2i& position) { _position = position; }

  //void setSize(const sf::Vector2u& size) { _size = size; }

  // Intersection check
  bool operator&(const IObject& other) {
    // TODO
    return false;
  }

 private:
  ObjectType _type;
  uint16_t _state;

  sf::Texture _texture;
  std::vector<sf::Sprite> _sprites;
};


#endif // BATTLECITY_OBJECT_H
