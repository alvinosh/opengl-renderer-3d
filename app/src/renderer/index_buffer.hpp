#pragma once

#include "error.hpp"

class IndexBuffer
{
private:
  uint32_t m_id;
  uint32_t m_count;

public:
  IndexBuffer(const uint32_t* data, uint32_t count);
  ~IndexBuffer();

  void bind() const;
  void unbind() const;

  uint32_t get_count() const { return m_count; }
};