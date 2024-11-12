#include "GameField.h"

#include "Objects/PlayerTank.h"
#include "Objects/Block.h"
#include "Objects/Border.h"
#include "Objects/Bush.h"

GameField::GameField(const std::vector<std::shared_ptr<IObject>>& objects, const std::vector<uint8_t>& tanks, const bool homebrewChanges) :
_objects(objects), _homebrew(homebrewChanges) {

  _objects.push_back(std::make_shared<Border>(0));
  _objects.push_back(std::make_shared<Border>(1));
  _objects.push_back(std::make_shared<Border>(2));
  _objects.push_back(std::make_shared<Border>(3));

  _objects.push_back(std::make_shared<PlayerTank>(sf::Vector2f(0, 0)));

  _objects.push_back(std::make_shared<Block>(sf::Vector2f(16, 16)));
  _objects.push_back(std::make_shared<Block>(sf::Vector2f(40, 16)));
  _objects.push_back(std::make_shared<Block>(sf::Vector2f(16, 40)));
  _objects.push_back(std::make_shared<Block>(sf::Vector2f(40, 40)));

  _objects.push_back(std::make_shared<Bush>(sf::Vector2f(24, 24)));
  _objects.push_back(std::make_shared<Bush>(sf::Vector2f(32, 24)));
  _objects.push_back(std::make_shared<Bush>(sf::Vector2f(24, 32)));
  _objects.push_back(std::make_shared<Bush>(sf::Vector2f(32, 32)));
}

std::vector<std::shared_ptr<IObject>> GameField::getObjects() const {
  return _objects;
}

void GameField::think(const Event &event) {
  for (size_t i = 0; i < _objects.size(); ++i) {
    auto object = _objects[i];
    if (object->isDestroyed()) {
      _objects.erase(_objects.begin() + i);
      --i;
      continue;
    }
    object->think(_objects, _globalClock, event);
  }
}
