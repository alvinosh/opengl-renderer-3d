#pragma once

#include "error.hpp"
#include "vertex.hpp"

#include <vector>

class VertexBuffer
{
private:
  uint32_t m_id;

public:
  VertexBuffer(const void* data, uint32_t size);
  VertexBuffer();
  VertexBuffer(std::vector<Vertex>& vert);
  ~VertexBuffer();

  void SetData(std::vector<Vertex>& vert);

  void Bind() const;
  void UnBind() const;
};