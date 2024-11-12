#pragma once

#include <string>
#include <vector>

#include "Event.h"
#include "Objects/IObject.h"

class GameField {
 public:
  GameField(const std::vector<std::shared_ptr<IObject>>& objects, const std::vector<uint8_t>& tanks, const bool homebrewChanges = true);
  GameField(const std::vector<std::string>& objects, const std::string& tanks, const bool homebrewChanges = true);

  std::vector<std::shared_ptr<IObject>> getObjects() const;
  void think(const Event& event);

 private:
  std::vector<std::shared_ptr<IObject>> _objects;
  bool _homebrew;

  sf::Clock _globalClock;
};
