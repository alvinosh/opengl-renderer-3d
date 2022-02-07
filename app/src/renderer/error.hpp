#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#define GLCALL(x)                                                              \
  gl_clear_error();                                                            \
  x;                                                                           \
  gl_log_error(#x, __FILE__, __LINE__)

void gl_clear_error();
bool gl_log_error(const char* function, const char* file, int line);