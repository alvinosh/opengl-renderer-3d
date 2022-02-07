#include "vertex_buffer_layout.hpp"

template <typename T>
void
VertexArrayLayout<T>::push(uint32_t count)
{
  std::cout << "lol" << std::endl;
}

template <> // GL_BYTE
void
VertexArrayLayout<int8_t>::push(uint32_t count)
{
  m_elements.push_back({ GL_BYTE, count, GL_FALSE });
  m_stride += VertexArrayElement::get_size(GL_BYTE);
}

template <> // GL_UNSIGNED_BYTE
void
VertexArrayLayout<uint8_t>::push(uint32_t count)
{
  m_elements.push_back({ GL_UNSIGNED_BYTE, count, GL_FALSE });
  m_stride += VertexArrayElement::get_size(GL_UNSIGNED_BYTE);
}

template <> // GL_INT
void
VertexArrayLayout<int32_t>::push(uint32_t count)
{
  m_elements.push_back({ GL_INT, count, GL_FALSE });
  m_stride += VertexArrayElement::get_size(GL_INT);
}

template <> // GL_UNSIGNED_INT
void
VertexArrayLayout<uint32_t>::push(uint32_t count)
{
  m_elements.push_back({ GL_UNSIGNED_INT, count, true });
  m_stride += VertexArrayElement::get_size(GL_UNSIGNED_INT);
}

template <> // GL_FLOAT
void
VertexArrayLayout<float>::push(uint32_t count)
{
  m_elements.push_back({ GL_FLOAT, count, true });
  m_stride += VertexArrayElement::get_size(GL_FLOAT);
}