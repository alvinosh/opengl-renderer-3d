#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>

#include "renderer.hpp"
#include "window.hpp"

int
main()
{
  Window window(600, 400, "My window", WindowMode::WINDOWED);

  Renderer3D renderer;

  float vertices[] = {
    // positions       // colors
    0.5f,  0.5f,  0.0f, 1.0f, 0.0f, 0.0f, // bottom right
    0.5f,  -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, // bottom left
    -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, // top
    -0.5f, 0.5f,  0.0f, 0.0f, 0.0f, 1.0f  // bottom top

  };
  unsigned int indices[] = {
    // note that we start from 0!
    0, 1, 3, // first triangle
    1, 2, 3  // second triangle
  };

  VertexBuffer vb(vertices, 6 * 4 * sizeof(float));

  VertexArray va;
  VertexArrayLayout layout;
  layout.push<float>(3);
  layout.push<float>(3);

  va.AddBuffer(vb, layout);

  IndexBuffer ib(indices, 6);

  Shader basic(
    std::string("E:\\dev\\cpp\\OpenGL\\app\\res\\shaders\\basic.glsl"));

#ifdef NDEBUG
  renderer.Wireframe(true);
#endif

  while (!window.ShouldClose()) {
    window.PollEvents();

    renderer.ClearColor(0.2f, 0.3f, 0.3f, 1.0f);

    renderer.Draw(va, ib, basic);

    window.SwapBuffers();
  }
  return 0;
}