#include "Window.h"

#include <cmath>
#include <memory>

#include "../../Other/Log.h"
#include "Drawables/IDrawable.h"

Window::Window() {
  auto screen = sf::VideoMode::getDesktopMode();
  _scale = std::max((uint8_t)std::min(screen.width / _width, screen.height / _height) - 1, 1);
  _window = std::make_unique<sf::RenderWindow>(
      sf::VideoMode(_width * _scale, _height * _scale),
      std::string("BattleCity client [") + CLIENT_VERSION + "]",
      sf::Style::Default
  );
  _window->setVerticalSyncEnabled(true);

  _transform.scale(_scale, _scale);
  Log::debug("Window created (" + std::to_string(_window->getSize().x) + "x" + std::to_string(_window->getSize().y) +
    " scale=" + std::to_string(_scale) + ")");
}

bool Window::isOpen() const {
  return _window->isOpen();
}

Event Window::pollEvent() {
  sf::Event SFMLevent{};
  if (_window->pollEvent(SFMLevent)) {
    switch (SFMLevent.type) {
      case sf::Event::Closed:
        _window->close();
        Log::info("Window closed");
        break;
      case sf::Event::Resized:
        // Align window to pixel perfect
        auto size = _window->getSize();
        uint8_t newScale = std::max(std::round(((double) size.x / _width + (double) size.y / _height) / 2), 1.0);
        auto newSize = sf::Vector2u(_width * newScale, _height * newScale);
        if (newSize == size) break;
        auto oldScale = _scale;
        _scale = newScale;
        _window->setSize(newSize);
        _window->setView(sf::View(sf::FloatRect(0, 0, _window->getSize().x, _window->getSize().y)));

        _transform.scale((double) _scale / oldScale, (double) _scale / oldScale);
        Log::debug(
            "Window resized to " + std::to_string(_window->getSize().x) + "x" + std::to_string(_window->getSize().y) +
            " (scale=" + std::to_string(_scale) + ")");
    }
  }

  Event event;
  if (_window->hasFocus()) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
      event.player1.up = true;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
      event.player1.left = true;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
      event.player1.down = true;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
      event.player1.right = true;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
      event.player1.shoot = true;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
      event.player2.up = true;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
      event.player2.left = true;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
      event.player2.down = true;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
      event.player2.right = true;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::RShift)) {
      event.player2.shoot = true;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
      event.player1.reset = true;
      event.player2.reset = true;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
      event.player1.esc = true;
      event.player2.esc = true;
    }
  }
  return event;
}

void Window::clear() const {
  _window->clear();
}

void Window::display() const {
  _window->display();
}

void Window::draw(const IDrawable& object) {
  for (const auto& sprite : object.getSprites()) {
    _window->draw(sprite, _transform);
  }
}
