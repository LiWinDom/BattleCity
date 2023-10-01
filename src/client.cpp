#include <SFML/Graphics.hpp>
#include <iostream>

uint8_t scale = 1;

int main()
{
  sf::RenderWindow window(sf::VideoMode(240, 208), "Battle City [beta 1.75]", sf::Style::Default);
  window.setVerticalSyncEnabled(true);

  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
      }
      if (event.type == sf::Event::Resized) {
        static uint8_t maxScale = std::min(sf::VideoMode::getDesktopMode().width / 240, sf::VideoMode::getDesktopMode().height / 208);

        double scaleX = window.getSize().x / 240.0;
        double scaleY = window.getSize().y / 208.0;

        scale = std::min(std::max((uint8_t)std::round((scaleX + scaleY) / 2), (uint8_t)1), maxScale);
        window.setSize(sf::Vector2u(240 * scale, 208 * scale));
      }
    }

    window.clear();

    window.display();
  }
}