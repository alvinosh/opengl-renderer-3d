#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

enum WindowMode
{
  WINDOWED = 0,
  FULLSCREEN = 1,
};

class Window
{
public:
  Window(uint16_t width, uint16_t height, const char* title, WindowMode wm);
  ~Window();

  bool ShouldClose() const noexcept;
  void PollEvents() const noexcept;
  void SwapBuffers() const noexcept;

  void SetResolution(uint32_t x, uint32_t y);

  void SetWindowed(uint32_t width = 0, uint32_t height = 0);
  void SetFullscreen(uint32_t width = 0, uint32_t height = 0);

  static void BufferResizeCB(GLFWwindow* window, int widht, int height);
  static void InputCB(GLFWwindow* window, int key, int scancode, int action,
                      int mods);

  GLFWwindow* GetNativeWindow() { return m_GLFWwindow; }

private:
  GLFWwindow* m_GLFWwindow;
  GLFWmonitor* m_GLFWmonitor;

  uint16_t m_WindowMode;

  uint16_t m_WindowWidth;
  uint16_t m_WindowHeight;
};