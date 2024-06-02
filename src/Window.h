#ifndef BATTLECITY_WINDOW_H
#define BATTLECITY_WINDOW_H

#include <SFML/Graphics.hpp>
#include <vector>

#include "IObject.h"

class Window final {
 public:
  Window();

  bool isOpen() const;

  sf::Event pollEvent();

  void clear() const;
  void display() const;


  void draw(IObject object) const;

  void draw(const std::vector<IObject>& objects) const {
    for (size_t i = 0; i < objects.size(); ++i) {
      draw(objects[i]);
    }
  }

  void draw(const IObject& object, const IObject& other...) const {
    draw(object);
    draw(other);
  }

  void draw(const std::vector<IObject>& objects, const std::vector<IObject>& other...) const {
    draw(objects);
    draw(other);
  }

 private:
  std::unique_ptr<sf::RenderWindow> _window;

  const uint8_t _width = 240, _height = 208;
  uint8_t _scale = 1;
};


#endif // BATTLECITY_WINDOW_H
