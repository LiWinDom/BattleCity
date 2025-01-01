#pragma once
#include <memory>
#include <vector>

#include <SFML/Graphics.hpp>

#include "../Event.h"
#include "Drawables/IDrawable.h"

class Window final {
 public:
  Window();

  bool isOpen() const;
  Event pollEvent();

  void clear() const;
  void display() const;

  void draw(const IDrawable& object);

 private:
  std::unique_ptr<sf::RenderWindow> _window;

  const uint8_t _width = 240, _height = 208;
  uint8_t _scale = 1;
  sf::Transform _transform;
};
