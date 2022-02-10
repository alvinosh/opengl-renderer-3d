#pragma once

#include "key_codes.hpp"
#include "mouse_codes.hpp"

#include "window.hpp"

class Input
{
private:
  Window* m_win;

public:
  Input(Window* win)
    : m_win(win)
  {
  }
  ~Input() = default;

  bool IsKeyPressed(KeyCode key);

  bool IsMouseButtonPressed(MouseCode button);
  float GetMouseX();
  float GetMouseY();
};
