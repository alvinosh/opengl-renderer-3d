#include "window.hpp"

Window::Window(uint16_t width, uint16_t height, const char* title,
               WindowMode wm)
{
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  m_WindowMode = wm;

  m_GLFWmonitor = glfwGetPrimaryMonitor();
  m_GLFWwindow = glfwCreateWindow(
    width, height, title, m_WindowMode == 1 ? m_GLFWmonitor : nullptr, nullptr);

  if (m_GLFWwindow == nullptr) {
    std::cout << "Failed to Initialize a GLFW Window" << std::endl;
    glfwTerminate();
  }

  glfwMakeContextCurrent(m_GLFWwindow);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    std::cout << "Failed to Initialize GLAD" << std::endl;
  }

  glViewport(0, 0, width, height);

  glfwSetWindowUserPointer(m_GLFWwindow, this);
  glfwSetWindowSizeCallback(m_GLFWwindow, Window::BufferResizeCB);
  glfwSetKeyCallback(m_GLFWwindow, Window::InputCB);

  std::cout << glGetString(GL_VERSION) << std::endl;
}

Window::~Window()
{
  glfwTerminate();
}

bool
Window::ShouldClose() const noexcept

{
  return glfwWindowShouldClose(m_GLFWwindow);
}

void
Window::PollEvents() const noexcept
{
  glfwPollEvents();
}

void
Window::SwapBuffers() const noexcept
{
  glfwSwapBuffers(m_GLFWwindow);
}

void
Window::BufferResizeCB(GLFWwindow* window, int width, int height)
{
  glViewport(0, 0, width, height);
}

void
Window::InputCB(GLFWwindow* window, int key, int scancode, int action, int mods)
{
  Window* _window = static_cast<Window*>(glfwGetWindowUserPointer(window));

  if (key == GLFW_KEY_E && action == GLFW_PRESS)
    glfwSetWindowShouldClose(window, true);
}
