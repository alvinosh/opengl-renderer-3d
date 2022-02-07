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
  VertexArrayLayout()
    : m_stride(0)
  {
  }

  template <typename T>
  inline void push(uint32_t count)
  {
    assert(false);
  }

  std::vector<VertexArrayElement> get_elements() const { return m_elements; }
  uint32_t get_stride() const { return m_stride; }
};

template <> // GL_BYTE
inline void
VertexArrayLayout::push<int8_t>(uint32_t count)
{
  m_elements.push_back({ GL_BYTE, count, GL_FALSE });
  m_stride += VertexArrayElement::get_size(GL_BYTE);
  m_stride += count * VertexArrayElement::get_size(GL_BYTE);
}

template <> // GL_UNSIGNED_BYTE
inline void
VertexArrayLayout::push<uint8_t>(uint32_t count)
{
  m_elements.push_back({ GL_UNSIGNED_BYTE, count, GL_FALSE });
  m_stride += count * VertexArrayElement::get_size(GL_UNSIGNED_BYTE);
}

template <> // GL_INT
inline void
VertexArrayLayout::push<int32_t>(uint32_t count)
{
  m_elements.push_back({ GL_INT, count, GL_FALSE });
  m_stride += count * VertexArrayElement::get_size(GL_INT);
}

template <> // GL_UNSIGNED_INT
inline void
VertexArrayLayout::push<uint32_t>(uint32_t count)
{
  m_elements.push_back({ GL_UNSIGNED_INT, count, GL_FALSE });
  m_stride += count * VertexArrayElement::get_size(GL_UNSIGNED_INT);
}

template <> // GL_FLOAT
inline void
VertexArrayLayout::push<float>(uint32_t count)
{
  m_elements.push_back({ GL_FLOAT, count, GL_FALSE });
  m_stride += count * VertexArrayElement::get_size(GL_FLOAT);
}