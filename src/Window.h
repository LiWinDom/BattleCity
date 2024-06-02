#ifndef BATTLECITY_WINDOW_H
#define BATTLECITY_WINDOW_H

#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>

#include "IObject.h"

class Window final {
 public:
  Window();

  bool isOpen() const;
  sf::Event pollEvent();

  void clear() const;
  void display() const;

  void draw(const IObject& object) const;
  void draw(const IObject& object, const IObject& other...) const;
  void draw(const std::vector<IObject>& objects) const;
  void draw(const std::vector<IObject>& objects, const std::vector<IObject>& other...) const;

 private:
  std::unique_ptr<sf::RenderWindow> _window;

  const uint8_t _width = 240, _height = 208;
  uint8_t _scale = 1;
  sf::Transform _transform;
};


#endif // BATTLECITY_WINDOW_H
