
#include <iostream>
#include "error.hpp"

void
glClearError()
{
  while (glGetError() != GL_NO_ERROR)
    ;
}

bool
glLogError(const char* function, const char* file, int line)
{
  while (GLenum err = glGetError()) {
    std::cout << "[OPENGL ERROR] (" << err << "): " << function << " " << file
              << " : " << line << std::endl;
    return false;
  }
  return true;
}