#include "Bonus.h"

#include "../Playfield/EagleProtection.h"
#include "ITank.h"

Bonus::Bonus(Game& game) : IObject(ObjectType::Bonus, {0, 0}, {16, 16}) {
  if (game.isHomebrew()) {
    _bonusType = static_cast<BonusType>(std::rand() % 6);
  }
  else {
    _bonusType = static_cast<BonusType>((std::rand() % 8) % 6);
    for (auto object : game.getObjects()) {
      if (object->getType() == ObjectType::Bonus) {
        object->destroy(game);
        break;
      }
    }
  }
  _collisionLayer = 2;

  do {
    _position = sf::Vector2f(std::rand() % 25 * 8, std::rand() % 25 * 8);
  }
  while (!getHardCollisions(game.getObjects()).empty());
}

uint8_t Bonus::getState() const {
  return _show << 3 | static_cast<uint8_t>(_bonusType);
}

void Bonus::think(Game &game, const Event &event) {
  _show = (int)(game.getTime() * 4) % 2;

  for (auto object : getHardCollisions(game.getObjects())) {
    if (object->getType() != ObjectType::PlayerTank && object->getType() != ObjectType::EnemyTank) {
      continue;
    }
    if (object->getType() == ObjectType::EnemyTank && !game.isHomebrew()) {
      continue;
    }
    auto tank = dynamic_cast<ITank*>(object.get());

    switch (_bonusType) {
      case BonusType::PlayerProtection:
        tank->addProtection(game);
        break;
      case BonusType::TimeFreezer:
        // Freeze all enemy tanks
        for (auto freezeObject : game.getObjects()) {
          if (freezeObject->getType() == ObjectType::PlayerTank || freezeObject->getType() == ObjectType::EnemyTank) {
            if (freezeObject->getType() != object->getType()) {
              dynamic_cast<ITank*>(freezeObject.get())->freeze(game);
            }
          }
        }
        break;
      case BonusType::EagleProtection:
        for (auto protectionObject : game.getObjects()) {
          if (protectionObject->getType() == ObjectType::EagleProtection) {
            auto eagleProtection = dynamic_cast<EagleProtection*>(protectionObject.get());
            if (object->getType() == ObjectType::PlayerTank) {
              eagleProtection->addProtection(game);
            }
            else {
              eagleProtection->removeProtection(game);
            }
          }
        }
        break;
      case BonusType::TankUpgrade:
        tank->upgrade();
        break;
      case BonusType::Granade:
        // Freeze all enemy tanks
        for (auto destroyObject : game.getObjects()) {
          if (destroyObject->getType() == ObjectType::PlayerTank || destroyObject->getType() == ObjectType::EnemyTank) {
            if (destroyObject->getType() != object->getType()) {
              auto destroyTank = dynamic_cast<ITank*>(destroyObject.get());
              // Make sure to destroy heavy tanks
              destroyTank->destroy(game);
              destroyTank->destroy(game);
              destroyTank->destroy(game);
              destroyTank->destroy(game);
            }
          }
        }
        break;
      case BonusType::Life:
        tank->addLife();
        break;
    }

    _desytroyed = true;
    break;
  }
}
