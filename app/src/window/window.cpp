#include "window.hpp"

Window::Window(uint16_t width, uint16_t height, const char* title)
{
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  m_GLFWwindow = glfwCreateWindow(width, height, title, nullptr, nullptr);

  if (m_GLFWwindow == nullptr) {
    std::cout << "Failed to Initialize a GLFW Window" << std::endl;
    glfwTerminate();
  }

  glfwMakeContextCurrent(m_GLFWwindow);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    std::cout << "Failed to Initialize GLAD" << std::endl;
  }

  glViewport(0, 0, width, height);
  glfwSetWindowSizeCallback(m_GLFWwindow, Window::buffer_resize_callback);

  std::cout << glGetString(GL_VERSION) << std::endl;
}

Window::~Window()
{
  glfwTerminate();
}

bool
Window::should_close() const noexcept

{
  return glfwWindowShouldClose(m_GLFWwindow);
}

void
Window::poll_events() const noexcept
{
  glfwPollEvents();
}

void
Window::swap_buffers() const noexcept
{
  glfwSwapBuffers(m_GLFWwindow);
}

void
Window::buffer_resize_callback(GLFWwindow* window, int width, int height)
{
  glViewport(0, 0, width, height);
}

void
Window::input_callback(GLFWwindow* window)
{
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(window, true);
}
