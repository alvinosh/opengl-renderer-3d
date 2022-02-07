#pragma once

#include <vector>

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
  }
};
class VertexArrayLayout
{
private:
  std::vector<VertexArrayElement> m_elements;
  uint32_t m_stride;

public:
  VertexArrayLayout();

  std::vector<VertexArrrayElements> get_elements() { return m_elements; }
  std::vector<VertexArrrayElements> get_stride() { return m_stride; }

  template <typename T> // GL_BYTE
  void push(uint32_t count);

  template <> // GL_BYTE
  void push<int8_t>(uint32_t count)
  {
    m_elements.push_back({ GL_BYTE, count, GL_FALSE });
    m_stride += VertexArrayElement::get_size(GL_BYTE);
  }

  template <> // GL_UNSIGNED_BYTE
  void push<uint8_t>(uint32_t count);
  {
    m_elements.push_back({ GL_UNSIGNED_BYTE, count, GL_FALSE });
    m_stride += VertexArrayElement::get_size(GL_UNSIGNED_BYTE);
  }

  template <> // GL_INT
  void push<int32_t>(uint32_t count)
  {
    m_elements.push_back({ GL_INT, count, GL_FALSE });
    m_stride += VertexArrayElement::get_size(GL_INT);
  }

  template <> // GL_UNSIGNED_INT
  void push<uint32_t>(uint32_t count)
  {
    m_elements.push_back({ GL_UNSIGNED_INT, count, true });
    m_stride += VertexArrayElement::get_size(GL_UNSIGNED_INT);
  }

  template <> // GL_FLOAT
  void push<float>(uint32_t count)
  {
    m_elements.push_back({ GL_FLOAT, count, true });
    m_stride += VertexArrayElement::get_size(GL_FLOAT);
  }
};