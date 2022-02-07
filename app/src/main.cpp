
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>

#include "renderer.hpp"
#include "window.hpp"

const bool debug = false;

int
main()
{
  Window window(600, 400, "My window");

  float vertices[] = {
    // positions         // colors
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

  va.add_buffer(vb, layout);

  IndexBuffer ib(indices, 6);

  Shader basic(
    std::string("E:\\dev\\cpp\\OpenGL\\app\\res\\shaders\\basic.glsl"));

  if (debug) {
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  }

  while (!window.should_close()) {
    window.poll_events();

    GLCALL(glClearColor(0.2f, 0.3f, 0.3f, 1.0f));
    GLCALL(glClear(GL_COLOR_BUFFER_BIT));

    basic.use();
    va.bind();
    ib.bind();
    GLCALL(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0));

    window.swap_buffers();
  }
  return 0;
}