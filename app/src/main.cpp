
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
    0.5f,  0.5f,  0.0f, 1.0f, 0.5f, // top right
    0.5f,  -0.5f, 0.0f, 0.7f, 0.2f, // bottom right
    -0.2f, -0.5f, 0.0f, 1.0f, 0.1f, // bottom left
    0.2f,  0.5f,  0.0f, 1.0f, 0.8f  // top left
  };

  uint32_t indices[] = {
    0, 1, 3, // first Triangle
    1, 2, 3  // second Triangle
  };

  uint32_t VAO;
  GLCALL(glGenVertexArrays(1, &VAO));
  GLCALL(glBindVertexArray(VAO));

  // VertexArrayBuffer va(vb);
  //

  VertexBuffer vb(vertices, 5 * 4 * sizeof(float));
  IndexBuffer ib(indices, 6);

  vb.bind();
  ib.bind();

  GLCALL(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float),
                               (void*)0));
  GLCALL(glEnableVertexAttribArray(0));

  GLCALL(glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float),
                               (void*)(3 * sizeof(float))));
  GLCALL(glEnableVertexAttribArray(1));

  vb.unbind();
  ib.unbind();
  GLCALL(glBindVertexArray(0));

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
    GLCALL(glBindVertexArray(VAO));
    ib.bind();
    GLCALL(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0));

    window.swap_buffers();
  }
  return 0;
}