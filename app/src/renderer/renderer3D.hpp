#pragma once

#include "error.hpp"
#include "vertex_array_buffer.hpp"
#include "index_buffer.hpp"
#include "shader.hpp"

class Renderer3D
{
public:
  void ClearColor(float r, float g, float b, float a);
  void ClearDepth();

  void Draw(VertexArray& va, IndexBuffer& ib, Shader& shader);

  void Wireframe(bool state);
};