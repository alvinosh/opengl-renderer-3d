#pragma once

#include <vector>
#include <assert.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

struct VertexArrayElement
{
  uint32_t type;
  uint32_t count;
  uint32_t normalized;

  static uint32_t get_size(uint32_t type)
  {
    switch (type) {
      case GL_BYTE:
        return sizeof(GLbyte);
      case GL_INT:
        return sizeof(GLbyte);
      case GL_UNSIGNED_BYTE:
        return sizeof(GLubyte);
      case GL_UNSIGNED_INT:
        return sizeof(GLuint);
      case GL_FLOAT:
        return sizeof(GLfloat);
    }
    assert(false);
    return 0;
  }
};
class VertexArrayLayout
{
private:
  std::vector<VertexArrayElement> m_elements;
  uint32_t m_stride;

public:
  VertexArrayLayout();

  std::vector<VertexArrayElement> get_elements() const { return m_elements; }
  uint32_t get_stride() const { return m_stride; }
};
