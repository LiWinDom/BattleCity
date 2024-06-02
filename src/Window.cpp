#include "Window.h"

#include <cmath>

#include "Log.h"

Window::Window() {
  auto screen = sf::VideoMode::getDesktopMode();
  _scale = std::min(screen.width / _width, screen.height / _height);
  _window = std::unique_ptr<sf::RenderWindow>(new sf::RenderWindow(
      sf::VideoMode(_width * _scale, _height * _scale),
      std::string("BattleCity client [") + CLIENT_VERSION + "]",
      sf::Style::Default
  ));
  _window->setVerticalSyncEnabled(true);

  _transform.scale(_scale, _scale);
  Log::info("Window created (" + std::to_string(_window->getSize().x) + "x" + std::to_string(_window->getSize().y) +
    " scale=" + std::to_string(_scale) + ")");
}

bool Window::isOpen() const {
  return _window->isOpen();
}

sf::Event Window::pollEvent() {
  sf::Event event;
  _window->pollEvent(event);
  switch (event.type) {
    case sf::Event::Closed:
      _window->close();
      Log::info("Window closed");

    case sf::Event::Resized:
      // Align window to pixel perfect
      auto size = _window->getSize();
      uint8_t newScale = std::max(std::round(((double)size.x / _width + (double)size.y / _height) / 2), 1.0);
      auto newSize = sf::Vector2u(_width * newScale, _height * newScale);
      if (newSize == size) break;
      _scale = newScale;
      _window->setSize(newSize);
      _window->setView(sf::View(sf::FloatRect(0, 0, _window->getSize().x, _window->getSize().y)));

      _transform.scale(_scale, _scale);
      Log::info("Window resized to " + std::to_string(_window->getSize().x) + "x" + std::to_string(_window->getSize().y) +
                " (scale=" + std::to_string(_scale) + ")");
  }
  return event;
}

void Window::clear() const {
  _window->clear();
}

void Window::display() const {
  _window->display();
}

void Window::draw(const IObject& object) const {
  _window->draw(object.getSprite(), _transform);
}

void Window::draw(const IObject &object, const IObject &other, ...) const {
  draw(object);
  draw(other);
}

void Window::draw(const std::vector<IObject> &objects) const {
  for (auto object : objects) {
    draw(object);
  }
}

void Window::draw(const std::vector<IObject> &objects, const std::vector<IObject> &other, ...) const {
  draw(objects);
  draw(other);
}
