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

  void Bind() const;
  void UnBind() const;

  uint32_t GetCount() const { return m_count; }
};