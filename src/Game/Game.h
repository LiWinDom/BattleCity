#pragma once

#include <memory>
#include <string>
#include <vector>

#include <SFML/System.hpp>

#include "Event.h"

class IObject;

class Game {
 public:
  Game(const uint8_t stage, const bool twoPlayers, const bool homebrewChanges = true);

  std::vector<std::shared_ptr<IObject>> getObjects() const;
  void addObject(std::shared_ptr<IObject> object);

  uint8_t getStage() const;
  std::vector<uint8_t> getTanks() const;

  bool isTwoPlayers() const;
  float getTime() const;
  float getPeriod() const;

  bool isGameOver() const;
  bool isFinished() const;

  void think(Event event);

 private:
  uint8_t _stage;
  bool _homebrew;
  bool _twoPlayers;
  std::vector<std::shared_ptr<IObject>> _objects;
  std::vector<uint8_t> _tanks;

  uint8_t _playerSpawnersLeft = 0;
  bool _gameOver = false;
  bool _gameOverLabel = false;

  float _finishedTime = -1;
  bool _finished = false;

  sf::Clock _globalClock;
  float _lastThink = 0;
  bool _paused = false;
};
