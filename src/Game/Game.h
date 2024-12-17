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

  float getTime() const;
  float getPeriod() const;

  void think(const Event& event);

 private:
  uint8_t _stage;
  bool _homebrew;
  bool _twoPlayers;
  std::vector<std::shared_ptr<IObject>> _objects;
  std::vector<uint8_t> _tanks;

  sf::Clock _globalClock;
  float _lastThink = 0;
};
