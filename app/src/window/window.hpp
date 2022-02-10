#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

enum WindowMode
{
  WINDOWED = 0,
  FULLSCREEN = 1,
  BORDERLESS = 2,
};

class Window
{
public:
  Window(uint16_t width, uint16_t height, const char* title, WindowMode wm);
  ~Window();

  bool ShouldClose() const noexcept;
  void PollEvents() const noexcept;
  void SwapBuffers() const noexcept;

  static void BufferResizeCB(GLFWwindow* window, int widht, int height);
  static void InputCB(GLFWwindow* window, int key, int scancode, int action,
                      int mods);

private:
  GLFWwindow* m_GLFWwindow;
  GLFWmonitor* m_GLFWmonitor;

  uint16_t m_WindowMode;
};