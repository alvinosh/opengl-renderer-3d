#include "vertex_array_buffer.hpp"

VertexArray::VertexArray()
{
  GLCALL(glGenVertexArrays(1, &m_id));
  GLCALL(glBindVertexArray(m_id));
}

VertexArray::~VertexArray()
{
  GLCALL(glDeleteVertexArrays(1, &m_id));
}

void
VertexArray::add_buffer(const VertexBuffer& vb, const VertexArrayLayout& vbl)
{
  vb.bind();
  const std::vector<VertexArrayElement> elem = vbl.get_elements();
  uint32_t offset = 0;
  for (int i = 0; i < elem.size(); i++) {
    GLCALL(glVertexAttribPointer(i, elem.at(i).count, elem.at(i).type,
                                 elem.at(i).normalized, vbl.get_stride(),
                                 (const void*)offset));
    GLCALL(glEnableVertexAttribArray(i));
    offset += elem.at(i).count * VertexArrayElement::get_size(elem.at(i).type);
  }
}

void
VertexArray::bind() const
{
  GLCALL(glBindVertexArray(m_id));
}

void
VertexArray::unbind() const
{
  GLCALL(glBindVertexArray(0));
}
