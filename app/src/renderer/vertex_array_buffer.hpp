#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "vertex_buffer_layout.hpp"
#include "vertex_buffer.hpp"
#include "error.hpp"

class VertexArray
{
private:
  uint32_t m_id;

public:
  VertexArray();
  ~VertexArray();

  void add_buffer(const& VertexBuffer, const& VertexBufferLayout);

  void bind() const;
  void unbind() const;
}
