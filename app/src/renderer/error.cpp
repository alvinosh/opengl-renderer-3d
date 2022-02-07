
#include <iostream>
#include "error.hpp"

void
gl_clear_error()
{
  while (glGetError() != GL_NO_ERROR)
    ;
}

bool
gl_log_error(const char* function, const char* file, int line)
{
  while (GLenum err = glGetError()) {
    std::cout << "[OPENGL ERROR] (" << err << "): " << function << " " << file
              << " : " << line << std::endl;
    return false;
  }
  return true;
}