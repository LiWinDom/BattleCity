#pragma once

struct PressedButtons {
  bool up = false;
  bool down = false;
  bool left = false;
  bool right = false;
  bool shoot = false;
  bool esc = false;
};

struct Event {
  PressedButtons player1, player2;
};
