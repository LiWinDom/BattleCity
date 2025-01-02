#pragma once

struct PressedButtons {
  bool up = false;
  bool down = false;
  bool left = false;
  bool right = false;
  bool shoot = false;
  bool esc = false;
  bool reset = false;

  PressedButtons operator| (PressedButtons other) const {
    other.up |= up;
    other.down |= down;
    other.left |= left;
    other.right |= right;
    other.shoot |= shoot;
    other.esc |= esc;
    other.reset |= esc;

    return other;
  }
};

struct Event {
  PressedButtons player1, player2;
};
