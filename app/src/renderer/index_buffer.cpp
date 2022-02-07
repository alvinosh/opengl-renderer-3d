#include "index_buffer.hpp"

IndexBuffer::IndexBuffer(const uint32_t* data, uint32_t count)
  : m_count(count)
{
  GLCALL(glGenBuffers(1, &m_id));
  GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id));
  GLCALL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), data,
                      GL_STATIC_DRAW));
}

IndexBuffer::~IndexBuffer()
{
  GLCALL(glDeleteBuffers(1, &m_id));
}

void
IndexBuffer::bind() const
{
  GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id));
}

void
IndexBuffer::unbind() const
{
  GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}
