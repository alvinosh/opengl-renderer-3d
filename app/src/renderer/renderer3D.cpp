#include "renderer3D.hpp"

void
Renderer3D::ClearColor(float r, float g, float b, float a)
{
  GLCALL(glClearColor(0.2f, 0.3f, 0.3f, 1.0f));
  GLCALL(glClear(GL_COLOR_BUFFER_BIT));
}

void
Renderer3D::ClearDepth()
{
  GLCALL(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
}

void
Renderer3D::Draw(VertexArray& va, IndexBuffer& ib, Shader& shader)
{
  shader.Use();
  ib.Bind();
  GLCALL(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, 0));
}

void
Renderer3D::Wireframe(bool state)
{
  GLCALL(glPolygonMode(GL_FRONT_AND_BACK, state ? GL_LINE : GL_FILL));
}
