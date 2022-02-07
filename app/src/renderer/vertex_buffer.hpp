#pragma once

#include "error.hpp"

class VertexBuffer
{
private:
  uint32_t m_id;

public:
  VertexBuffer(const void* data, uint32_t size);
  ~VertexBuffer();

  void bind() const;
  void unbind() const;
};