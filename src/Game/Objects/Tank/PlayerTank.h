#pragma

#include "../Playfield/TankSpawner.h"
#include "ITank.h"

class PlayerTank : public ITank {
 public:
  PlayerTank(TankSpawner* spawner, uint8_t tankType = 0);

  uint8_t getState() const override;

  void think(Game& game, const Event& event) override;

  void upgrade() override;
  void addLife() override;

 private:
  TankSpawner* _spawnerPointer;
};
