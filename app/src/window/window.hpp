#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

class Window
{
public:
  Window(uint16_t width, uint16_t height, const char* title);
  ~Window();

  bool should_close() const noexcept;
  void poll_events() const noexcept;
  void swap_buffers() const noexcept;

  static void buffer_resize_callback(GLFWwindow* window, int widht, int height);
  static void input_callback(GLFWwindow* window);

private:
  GLFWwindow* m_GLFWwindow;
};