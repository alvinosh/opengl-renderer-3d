// #define NDEBUG
// #define FPS

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

  Mesh heart_mesh("E:\\dev\\cpp\\OpenGL\\app\\res\\models\\cuteheart.obj");
  Mesh cube_mesh("E:\\dev\\cpp\\OpenGL\\app\\res\\models\\cub.obj");

  Texture texture("E:\\dev\\cpp\\OpenGL\\app\\res\\textures\\wood.jpg");
  texture.Bind();

  Shader cube(
    std::string("E:\\dev\\cpp\\OpenGL\\app\\res\\shaders\\lighting.glsl"));

  // cube.SetInt("u_Texture", 0);

  Shader light(
    std::string("E:\\dev\\cpp\\OpenGL\\app\\res\\shaders\\light.glsl"));

  glm::vec3 lightColor(1.0f, 1.0f, 1.0f);
  glm::vec3 toyColor(1.0f, 0.5f, 0.31f);

  glm::vec3 lightPos(10.0f, 0.0f, 10.0f);

  float deltaTime = 0.0f;
  float lastFrame = 0.0f;

#ifdef NDEBUG
  renderer.Wireframe(true);
#endif

  while (!window.ShouldClose()) {
    window.PollEvents();

    float currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

    float fps = 1.0f / deltaTime;

#ifdef FPS
    std::cout << fps << std::endl;
#endif
    camera.InputHandler(input, deltaTime);

    if (input.IsKeyPressed(KeyCode::T))
      window.HideCursor(true);
    if (input.IsKeyPressed(KeyCode::G))
      window.HideCursor(false);

    renderer.ClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    renderer.ClearDepth();

    // lightPos.x = cos(glfwGetTime()) * 10.0f;
    // lightPos.z = sin(glfwGetTime()) * 10.0f;
    // lightPos.y = sin(glfwGetTime()) * 10.0f;

    glm::mat4 model = glm::mat4(1.0f);

    cube.Use();
    cube.SetMat4("view", camera.GetView());
    cube.SetMat4("projection", camera.GetProjection());
    cube.SetMat4("model", model);
    cube.SetVec3("objectColor", toyColor);
    cube.SetVec3("lightColor", lightColor);
    cube.SetVec3("lightPos", lightPos);
    cube.SetVec3("viewPos", camera.transform.m_position);

    model = glm::mat4(1.0f);
    model = glm::scale(model, glm::vec3(0.2f));
    model = glm::translate(model, lightPos);

    light.Use();
    light.SetMat4("view", camera.GetView());
    light.SetMat4("projection", camera.GetProjection());
    light.SetMat4("model", model);

    renderer.Draw(heart_mesh.va, heart_mesh.ib, cube);
    renderer.Draw(cube_mesh.va, cube_mesh.ib, light);

    window.SwapBuffers();
  }
  return 0;
}