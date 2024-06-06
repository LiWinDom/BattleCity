#ifndef BATTLECITY_WINDOW_H
#define BATTLECITY_WINDOW_H

#include "SFML/Graphics.hpp"
#include <memory>
#include <vector>

#include "../Event.h"
#include "Drawable.h"

class Window final {
 public:
  Window();

  bool isOpen() const;
  Event pollEvent();

  void clear() const;
  void display() const;

  void draw(const Drawable& object);

 private:
  std::unique_ptr<sf::RenderWindow> _window;

  const uint8_t _width = 240, _height = 208;
  uint8_t _scale = 1;
  sf::Transform _transform;
};


#endif // BATTLECITY_WINDOW_H
