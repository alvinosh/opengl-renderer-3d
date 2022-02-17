#pragma once

#include <vector>

#include "vertex_array_buffer.hpp"
#include "index_buffer.hpp"

class Mesh
{
public:
  Mesh(const char* path);
  ~Mesh() = default;

  std::string name;

  uint32_t count;

  VertexArray va;
  VertexBuffer vb;
  IndexBuffer ib;

private:
};