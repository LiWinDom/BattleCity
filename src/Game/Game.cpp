#include "Game.h"

#include "Objects/Border.h"
#include "Objects/Brick.h"
#include "Objects/Bush.h"
#include "Objects/EnemyTank.h"
#include "Objects/PlayerTank.h"
#include "Objects/Wall.h"

Game::Game(const std::vector<std::shared_ptr<IObject>>& objects, const std::vector<uint8_t>& tanks, const bool homebrewChanges) :
_objects(objects), _tanks(tanks), _homebrew(homebrewChanges) {
  _objects.push_back(std::make_shared<Border>(0));
  _objects.push_back(std::make_shared<Border>(1));
  _objects.push_back(std::make_shared<Border>(2));
  _objects.push_back(std::make_shared<Border>(3));
}

Game::Game(const std::vector<std::string>& objects, const std::string& tanks, const bool homebrewChanges) :
Game(std::vector<std::shared_ptr<IObject>>(0), {}, homebrewChanges) {
  if (objects.size() != 26) {
    throw std::invalid_argument("Objects matrix must be 26x26");
  }
  for (auto i = 0; i < objects.size(); ++i) {
    if (objects[i].size() != 26) {
      throw std::invalid_argument("Objects matrix must be 26x26");
    }
    for (auto j = 0; j < objects[i].size(); ++j) {
      const sf::Vector2f pos(j * 8, i * 8);
      switch (objects[i][j]) {
        case 'b':
          _objects.push_back(std::make_shared<Brick>(pos));
          break;
        case 'w':
          _objects.push_back(std::make_shared<Wall>(pos));
          break;
        case 'B':
          _objects.push_back(std::make_shared<Bush>(pos));
          break;
        case 'W':
          // TODO: water
          break;
        case 'i':
          // TODO: ice
          break;
        case 'e':
          // TODO: eagle
          break;
        case 's':
          // TODO: spawn pos
          _objects.push_back(std::make_shared<EnemyTank>(pos, 0));
          break;
        case '1':
          _objects.push_back(std::make_shared<PlayerTank>(pos));
          break;
        case '2':
          _objects.push_back(std::make_shared<PlayerTank>(pos, true));
          break;
      }
    }
  }
}

std::vector<std::shared_ptr<IObject>> Game::getObjects() const {
  return _objects;
}

void Game::addObject(std::shared_ptr<IObject> object) {
  _objects.push_back(object);
}

float Game::getTime() const {
  return _globalClock.getElapsedTime().asSeconds();
}

void Game::think(const Event &event) {
  // Removing destroyed objects
  for (size_t i = 0; i < _objects.size(); ++i) {
    auto object = _objects[i];
    if (object->isDestroyed()) {
      _objects.erase(_objects.begin() + i);
      --i;
      continue;
    }
  }

  // Simulating 60 fps
  while (getTime() + 1.0/60 > _lastThink) {
    _lastThink += 1.0/60;
    for (size_t i = 0; i < _objects.size(); ++i) {
      auto object = _objects[i];
      if (object->isDestroyed()) {
        continue;
      }
      object->think(*this, event);
    }
  }
}
