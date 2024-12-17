#include "Game.h"

#include <fstream>

#include "../Other/Path.h"
#include "Enums.h"
#include "Objects/Border.h"
#include "Objects/Brick.h"
#include "Objects/Bush.h"
#include "Objects/EnemyTank.h"
#include "Objects/TankSpawner.h"
#include "Objects/Wall.h"

Game::Game(const uint8_t stage, const bool twoPlayers, const bool homebrewChanges) :
_stage(stage), _twoPlayers(twoPlayers), _homebrew(homebrewChanges) {
  // Trying to load stage info
  const auto path = Path::getAbsolutePath(std::format("resources/stages/stage{}.layout", _stage));
  std::ifstream layoutFile(Path::getAbsolutePath(std::format("resources/stages/stage{}.layout", _stage)));
  std::ifstream tanksFile(Path::getAbsolutePath(std::format("resources/stages/stage{}.tanks", _stage)));

  if (!layoutFile.is_open() || !tanksFile.is_open()) {
    throw std::runtime_error(std::format("Failed to load data for stage {}", _stage));
  }

  for (size_t i = 0; i < 26; ++i) {
    std::string row;
    std::getline(layoutFile, row);

    if (row.size() != 26) {
      throw std::invalid_argument("Layout matrix must be 26x26");
    }
    for (auto j = 0; j < row.size(); ++j) {
      const sf::Vector2f pos(j * 8, i * 8);
      switch (row[j]) {
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
          _objects.push_back(std::make_shared<TankSpawner>(pos, ObjectType::PlayerTank, 0));
          break;
        case '2':
          if (_twoPlayers) {
            _objects.push_back(std::make_shared<TankSpawner>(pos, ObjectType::PlayerTank, 1));
          }
          break;
      }
    }
  }

  std::string tanks;
  std::getline(tanksFile, tanks);
  for (const auto tank : tanks) {
    _tanks.push_back(std::atoi(&tank));
  }

  layoutFile.close();
  tanksFile.close();

  // Adding borders
  _objects.push_back(std::make_shared<Border>(0));
  _objects.push_back(std::make_shared<Border>(1));
  _objects.push_back(std::make_shared<Border>(2));
  _objects.push_back(std::make_shared<Border>(3));
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

float Game::getPeriod() const {
  return 190 - _stage * 4 - (_twoPlayers ? 2 : 1 - 1) * 20;
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
