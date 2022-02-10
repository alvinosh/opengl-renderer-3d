#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "vertex_array_layout.hpp"
#include "vertex_buffer.hpp"
#include "error.hpp"

class VertexArray
{
private:
  uint32_t m_id;

public:
  VertexArray();
  ~VertexArray();

  void AddBuffer(const VertexBuffer& vb, const VertexArrayLayout& vbl);

  void Bind() const;
  void UnBind() const;
};
