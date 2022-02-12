// #define NDEBUG

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "renderer.hpp"
#include "window.hpp"
#include "input.hpp"
#include "camera.hpp"
#include "mesh.hpp"

int
main()
{
  Window window(600, 400, "My window", WindowMode::WINDOWED);

  Input input(&window);

  Renderer3D renderer;

  Camera camera(glm::radians(45.0f),
                (float)window.GetWidth() / (float)window.GetHeight(), 0.1f,
                100.0f);

  Mesh mesh("E:\\dev\\cpp\\OpenGL\\app\\res\\models\\heart.obj");

  float vertices[] = {
    // positions        // colors
    0.5f,  0.5f,  0.0f, //
    0.5f,  -0.5f, 0.0f, //
    -0.5f, -0.5f, 0.0f, //
    -0.5f, 0.5f,  0.0f, //
    0.5f,  0.5f,  1.0f, //
    0.5f,  -0.5f, 1.0f, //
    -0.5f, -0.5f, 1.0f, //
    -0.5f, 0.5f,  1.0f, //

  };
  unsigned int indices[] = {
    // note that we start from 0!
    0, 1, 3, // first triangle
    3, 1, 2, //
    3, 7, 0, //
    0, 7, 4, //
    0, 4, 5, //
    0, 5, 1, //
    7, 3, 2, //
    7, 2, 6, //
    2, 5, 6, //
    2, 1, 5, //
    4, 6, 5, //
    4, 7, 6, //

  };

  VertexBuffer vb(vertices, 3 * 8 * sizeof(float));

  VertexArray va;
  VertexArrayLayout layout;
  layout.push<float>(3);
  va.AddBuffer(vb, layout);

  VertexArray la;
  la.AddBuffer(vb, layout);

  IndexBuffer ib(indices, 12 * 3);

  Shader cube(
    std::string("E:\\dev\\cpp\\OpenGL\\app\\res\\shaders\\lighting.glsl"));

  Shader light(
    std::string("E:\\dev\\cpp\\OpenGL\\app\\res\\shaders\\light.glsl"));

  glm::vec3 lightColor(1.0f, 1.0f, 1.0f);
  glm::vec3 toyColor(1.0f, 0.5f, 0.31f);

  glm::vec3 lightPos(5.2f, 1.0f, 2.0f);

#ifdef NDEBUG
  renderer.Wireframe(true);
#endif

  while (!window.ShouldClose()) {
    window.PollEvents();

    const float cameraSpeed = 0.05f;
    if (input.IsKeyPressed(KeyCode::W))
      camera.MoveForward(1);
    if (input.IsKeyPressed(KeyCode::S))
      camera.MoveForward(-1);
    if (input.IsKeyPressed(KeyCode::A))
      camera.MoveSide(-1);
    if (input.IsKeyPressed(KeyCode::D))
      camera.MoveSide(1);
    if (input.IsKeyPressed(KeyCode::LeftShift))
      camera.MoveUp(-1);
    if (input.IsKeyPressed(KeyCode::Space))
      camera.MoveUp(1);

    if (input.IsKeyPressed(KeyCode::T))
      window.HideCursor(true);
    if (input.IsKeyPressed(KeyCode::G))
      window.HideCursor(false);

    double delta_x, delta_y;
    float sensitivity = 0.05f;
    input.GetMouseDelta(&delta_x, &delta_y);
    delta_x *= sensitivity;
    delta_y *= sensitivity;

    camera.transform.m_rotation.x += delta_y;
    camera.transform.m_rotation.y += delta_x;

    if (camera.transform.m_rotation.x > 89.0f)
      camera.transform.m_rotation.x = 89.0f;
    if (camera.transform.m_rotation.x < -89.0f)
      camera.transform.m_rotation.x = -89.0f;

    renderer.ClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    renderer.ClearDepth();

    glm::mat4 model = glm::mat4(1.0f);
    model =
      glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));

    cube.Use();

    cube.SetMat4("view", camera.GetView());
    cube.SetMat4("projection", camera.GetProjection());
    cube.SetMat4("model", model);

    cube.SetVec3("objectColor", toyColor);
    cube.SetVec3("lightColor", lightColor);

    model = glm::mat4(1.0f);
    model = glm::scale(model, glm::vec3(0.2f));
    model = glm::translate(model, lightPos);

    light.Use();
    light.SetMat4("view", camera.GetView());
    light.SetMat4("projection", camera.GetProjection());
    light.SetMat4("model", model);

    renderer.Draw(va, ib, cube);
    renderer.Draw(la, ib, light);

    window.SwapBuffers();
  }
  return 0;
}