#include "index_buffer.hpp"

IndexBuffer::IndexBuffer(const uint32_t* data, uint32_t count)
  : m_count(count)
{
  GLCALL(glGenBuffers(1, &m_id));
  GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id));
  GLCALL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), data,
                      GL_STATIC_DRAW));
}

IndexBuffer::IndexBuffer()
{
  GLCALL(glGenBuffers(1, &m_id));
}

IndexBuffer::~IndexBuffer()
{
  GLCALL(glDeleteBuffers(1, &m_id));
}

void
IndexBuffer::SetData(std::vector<uint32_t> indicies)
{

  m_count = indicies.size();

  GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id));
  GLCALL(glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                      indicies.size() * sizeof(uint32_t), &indicies.front(),
                      GL_STATIC_DRAW));
}

void
IndexBuffer::Bind() const
{
  GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id));
}

void
IndexBuffer::UnBind() const
{
  GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}
