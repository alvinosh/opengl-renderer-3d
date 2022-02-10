#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#define GLCALL(x)                                                              \
  glClearError();                                                              \
  x;                                                                           \
  glLogError(#x, __FILE__, __LINE__)

void glClearError();
bool glLogError(const char* function, const char* file, int line);