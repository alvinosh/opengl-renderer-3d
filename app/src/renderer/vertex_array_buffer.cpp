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
VertexArray::AddBuffer(const VertexBuffer& vb, const VertexArrayLayout& vbl)
{
  vb.Bind();
  const std::vector<VertexArrayElement> elem = vbl.get_elements();
  uint32_t offset = 0;
  for (int i = 0; i < elem.size(); i++) {
    // std::cout << i << "\n" << elem.at(i).count << "\n" << elem.at(i).type
    //           << "\n" << elem.at(i).normalized << "\n" << vbl.get_stride()
    //           << "\n" << offset << "\n" << std::endl;

    GLCALL(glVertexAttribPointer(i, elem.at(i).count, elem.at(i).type,
                                 elem.at(i).normalized, vbl.get_stride(),
                                 (const void*)offset));
    GLCALL(glEnableVertexAttribArray(i));
    offset += elem.at(i).count * VertexArrayElement::get_size(elem.at(i).type);
  }
}

void
VertexArray::Bind() const
{
  GLCALL(glBindVertexArray(m_id));
}

void
VertexArray::UnBind() const
{
  GLCALL(glBindVertexArray(0));
}
