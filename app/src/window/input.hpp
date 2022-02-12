#pragma once

#include "key_codes.hpp"
#include "mouse_codes.hpp"

#include "window.hpp"

class Input
{
private:
  Window* m_win;

  double m_lastmousex;
  double m_lastmousey;

  bool m_firstmouse;

public:
  Input(Window* win)
    : m_win(win)
    , m_firstmouse(true)
  {
  }
  ~Input() = default;

  bool IsKeyPressed(KeyCode key);

  bool IsMouseButtonPressed(MouseCode button);
  float GetMouseX();
  float GetMouseY();

  void GetMouseDelta(double* deltax, double* deltay);
};
