#include "Game.h"

#include <fmt/format.h>
#include <fstream>

#include "../Other/Log.h"
#include "Objects/Objects.h"

Game::Game(const uint8_t stage, const bool twoPlayers, const bool homebrewChanges) :
_stage(stage), _twoPlayers(twoPlayers), _homebrew(homebrewChanges) {
  // Trying to load stage info
  const auto path = Path::getAbsolutePath(fmt::format("resources/stages/stage{}.layout", _stage));
  std::ifstream layoutFile(Path::getAbsolutePath(fmt::format("resources/stages/stage{}.layout", _stage)));
  std::ifstream tanksFile(Path::getAbsolutePath(fmt::format("resources/stages/stage{}.tanks", _stage)));

  if (!layoutFile.is_open() || !tanksFile.is_open()) {
    throw std::runtime_error(fmt::format("Failed to load data for stage {}", _stage));
  }

  for (size_t i = 0; i < 26; ++i) {
    std::string row;
    std::getline(layoutFile, row);

    uint8_t enemySpawnerNum = 1;
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
          _objects.push_back(std::make_shared<Water>(pos));
          break;
        case 'i':
          // TODO: ice
          break;
        case 'p':
          // TODO: protection
          _objects.push_back(std::make_shared<Brick>(pos));
          break;
        case 'e':
          _objects.push_back(std::make_shared<Eagle>(pos));
          break;
        case 's':
          _objects.push_back(std::make_shared<TankSpawner>(pos, ObjectType::EnemyTank, enemySpawnerNum = (enemySpawnerNum + 1) % 3));
          break;
        case '1':
          _objects.push_back(std::make_shared<TankSpawner>(pos, ObjectType::PlayerTank, 0));
          ++_playerSpawnersLeft;
          break;
        case '2':
          if (_twoPlayers) {
            _objects.push_back(std::make_shared<TankSpawner>(pos, ObjectType::PlayerTank, 1));
            ++_playerSpawnersLeft;
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
  // Interface objects
  _objects.push_back(std::make_shared<StageNumber>());

  std::srand(std::time(nullptr));
  Log::info(fmt::format("Game started, stage {}", _stage));
}

std::vector<std::shared_ptr<IObject>> Game::getObjects() const {
  return _objects;
}

void Game::addObject(std::shared_ptr<IObject> object) {
  _objects.push_back(object);
}

uint8_t Game::getStage() const {
  return _stage;
}

std::vector<uint8_t> Game::getTanks() const {
  return _tanks;
}

bool Game::isTwoPlayers() const {
  return _twoPlayers;
}

float Game::getTime() const {
  return _lastThink;
}

float Game::getPeriod() const {
  return (190 - _stage * 4 - (_twoPlayers ? 2 : 1 - 1) * 20) / 60.0;
}

bool Game::isGameOver() const {
  return _gameOver;
}

bool Game::isFinished() const {
  return _finished;
}

void Game::think(Event event) {
  size_t tanksLeft = 0;
  size_t spawnersLeft = 0;

  // Removing destroyed objects
  for (size_t i = 0; i < _objects.size(); ++i) {
    auto object = _objects[i];

    // Special conditions
    switch (object->getType()) {
      case ObjectType::Eagle:
        if (object->getState()) {
          _gameOver = true;
        }
        break;
      case ObjectType::EnemyTank:
        ++tanksLeft;
        break;
      case ObjectType::Spawner:
        if (std::dynamic_pointer_cast<TankSpawner>(object)->getSpawnObject() == ObjectType::PlayerTank) {
          ++spawnersLeft;
        }
        else {
          ++tanksLeft;
        }
        break;
    }

    if (object->isDestroyed()) {
      _objects.erase(_objects.begin() + i);
      --i;
    }
  }
  if (spawnersLeft == 0) {
    _gameOver = true;
  }

  // Creating game over label
  if (_gameOver) {
    event = Event();
    if (!_gameOverLabel) {
      addObject(std::make_shared<GameOver>());
      _gameOverLabel = true;
    }
  }

  // Simulating 60 fps
  while (_globalClock.getElapsedTime().asSeconds() + 1.0 / 60 > _lastThink) {
    if (!_paused) {
      for (const auto object : _objects) {
        if (object->isDestroyed()) {
          continue;
        }
        object->think(*this, event);
      }

      // Preparing for level change
      if (tanksLeft == 0) {
        if (_finishedTime == -1) {
          _finishedTime = getTime();
        }
        if (_finishedTime + getPeriod() * 2 < getTime()) {
          _finished = true;
        }
      }
      else {
        _finishedTime = -1;
      }
    }
    _lastThink += 1.0 / 60;
  }
}
