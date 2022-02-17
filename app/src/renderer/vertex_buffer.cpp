#include "vertex_buffer.hpp"

#include <iostream>

VertexBuffer::VertexBuffer(const void* data, uint32_t size)
{
  GLCALL(glGenBuffers(1, &m_id));
  GLCALL(glBindBuffer(GL_ARRAY_BUFFER, m_id));
  GLCALL(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
}

VertexBuffer::VertexBuffer()
{
  GLCALL(glGenBuffers(1, &m_id));
}

VertexBuffer::VertexBuffer(std::vector<Vertex>& vert)
{

  GLCALL(glGenBuffers(1, &m_id));
  GLCALL(glBindBuffer(GL_ARRAY_BUFFER, m_id));
  GLCALL(glBufferData(GL_ARRAY_BUFFER, vert.size() * sizeof(Vertex),
                      &vert.front(), GL_STATIC_DRAW));
}

VertexBuffer::~VertexBuffer()
{
  GLCALL(glDeleteBuffers(1, &m_id));
}

void
VertexBuffer::SetData(std::vector<Vertex>& vert)
{
  GLCALL(glBindBuffer(GL_ARRAY_BUFFER, m_id));
  GLCALL(glBufferData(GL_ARRAY_BUFFER, vert.size() * sizeof(Vertex),
                      &vert.front(), GL_STATIC_DRAW));
}

void
VertexBuffer::Bind() const
{
  GLCALL(glBindBuffer(GL_ARRAY_BUFFER, m_id));
}

void
VertexBuffer::UnBind() const
{
  GLCALL(glBindBuffer(GL_ARRAY_BUFFER, 0));
}
