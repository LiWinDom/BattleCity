#pragma once

#include <string>
#include <vector>

#include <SFML/System.hpp>

#include "Event.h"

class IObject;

class Game {
 public:
  Game(const std::vector<std::shared_ptr<IObject>>& objects, const std::vector<uint8_t>& tanks, const bool homebrewChanges = true);
  Game(const std::vector<std::string>& objects, const std::string& tanks, const bool homebrewChanges = true);

  std::vector<std::shared_ptr<IObject>> getObjects() const;
  void addObject(std::shared_ptr<IObject> object);

  float getTime() const;

  void think(const Event& event);

 private:
  std::vector<std::shared_ptr<IObject>> _objects;
  std::vector<uint8_t> _tanks;
  bool _homebrew;

  sf::Clock _globalClock;
  float _lastThink = 0;
};
