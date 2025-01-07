#pragma once

#include "../IMovable.h"
#include "Bullet.h"
#include "TankProtection.h"

class ITank : public IMovable {
 public:
  ITank(ObjectType type, const sf::Vector2f& position);

  uint8_t getTankType();
  uint8_t isBonus() const;

  uint8_t getState() const override;

  void think(Game& game, const Event& event) override;

  void destroy(Game& game, const ObjectRotation& bulletRotation = ObjectRotation::Up) override;

  void shoot(Game& game);

  // Bonus things
  void addProtection(Game& game, float time = 10);
  void freeze(Game& game, float time = 10);
  virtual void upgrade() = 0;
  virtual void addLife() = 0;

 protected:
  uint8_t _tankType = 0;
  uint8_t _livesNum = 0;
  bool _hasBonus = false;

  uint8_t _maxBullets = 1;
  bool _fastBullets = false;
  bool _powerfulBullets = false;
  std::vector<std::shared_ptr<IObject>> _bullets;

  float _protectedUntil = -1;

  // For enemy tank
  bool _failedToMove = false;

 private:
  static void snap(float& coordinate);

  bool _wheelState = false;

  float _lastShotTime = -1;
  float _frozenUntil = -1;
};
