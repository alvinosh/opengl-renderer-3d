#include "window.hpp"

Window::Window(uint16_t width, uint16_t height, const char* title,
               WindowMode wm)
{
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  m_WindowMode = wm;

  m_GLFWmonitor = glfwGetPrimaryMonitor();
  m_GLFWwindow = glfwCreateWindow(
    width, height, title, m_WindowMode == 1 ? m_GLFWmonitor : nullptr, nullptr);

  switch (m_WindowMode) {
    case WindowMode::FULLSCREEN:
      SetFullscreen();
      break;
      // case WindowMode::WINDOWED:
      //   SetWindowed(width, height);
      //   break;
  }

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

  glEnable(GL_DEPTH_TEST);

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
Window::HideCursor(bool value)
{
  glfwSetInputMode(m_GLFWwindow, GLFW_CURSOR,
                   value ? GLFW_CURSOR_DISABLED : GLFW_CURSOR_NORMAL);
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
Window::SetResolution(uint32_t x, uint32_t y)
{
  glViewport(0, 0, x, y);
}

int32_t
Window::GetWidth() const
{
  int32_t res;
  glfwGetWindowSize(m_GLFWwindow, &res, nullptr);
  return res;
}

int32_t
Window::GetHeight() const
{
  int32_t res;
  glfwGetWindowSize(m_GLFWwindow, nullptr, &res);
  return res;
}

void
Window::SetWindowed(uint32_t width, uint32_t height)
{
  const GLFWvidmode* mode = glfwGetVideoMode(m_GLFWmonitor);
  glfwSetWindowMonitor(m_GLFWwindow, nullptr, 0, 0, width, height,
                       mode->refreshRate);
  m_WindowMode = WindowMode::WINDOWED;
}

void
Window::SetFullscreen(uint32_t width, uint32_t height)
{
  const GLFWvidmode* mode = glfwGetVideoMode(m_GLFWmonitor);

  glfwSetWindowMonitor(m_GLFWwindow, m_GLFWmonitor, 0, 0,
                       width == 0 ? mode->width : width,
                       height == 0 ? mode->height : height, mode->refreshRate);

  m_WindowMode = WindowMode::FULLSCREEN;
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
