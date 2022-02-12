#include "input.hpp"

bool
Input::IsKeyPressed(KeyCode key)
{
  auto state = glfwGetKey(m_win->GetNativeWindow(), static_cast<int32_t>(key));
  return state == GLFW_PRESS || state == GLFW_REPEAT;
}

bool
Input::IsMouseButtonPressed(MouseCode button)
{
  auto state =
    glfwGetMouseButton(m_win->GetNativeWindow(), static_cast<int32_t>(button));
  return state == GLFW_PRESS;
}

float
Input::GetMouseX()
{
  double pos;
  glfwGetCursorPos(m_win->GetNativeWindow(), &pos, nullptr);
  return pos;
}

float
Input::GetMouseY()
{
  double pos;
  glfwGetCursorPos(m_win->GetNativeWindow(), nullptr, &pos);
  return pos;
}

void
Input::GetMouseDelta(double* deltax, double* deltay)
{
  if (m_firstmouse) {
    m_lastmousex = GetMouseX();
    m_lastmousey = GetMouseY();
    m_firstmouse = false;
  }

  *deltax = GetMouseX() - m_lastmousex;
  *deltay = m_lastmousey - GetMouseY();
  m_lastmousex = GetMouseX();
  m_lastmousey = GetMouseY();
}
