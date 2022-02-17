#include "camera.hpp"

Camera::Camera(float fov, float aratio, float near, float far)
  : m_fov(fov)
  , m_ratio(aratio)
  , m_near(near)
  , m_far(far)
{

  m_cameraspeed = 0.05f;

  m_projection = glm::perspective(m_fov, m_ratio, m_near, m_far);

  m_view = glm::lookAt(transform.GetPosition(),
                       transform.GetPosition() + m_camerafront, m_cameraup);

  m_camerafront = glm::vec3(0.0f, 0.0f, 1.0f);
  m_cameraup = glm::vec3(0.0f, 1.0f, 0.0f);
}

glm::mat4
Camera::GetProjection()
{
  m_projection = glm::perspective(m_fov, m_ratio, m_near, m_far);
  return m_projection;
}

glm::mat4
Camera::GetView()
{

  float pitch = transform.m_rotation.x;
  float yaw = transform.m_rotation.y;

  glm::vec3 direction;
  direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
  direction.y = sin(glm::radians(pitch));
  direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

  m_camerafront = glm::normalize(direction);

  m_view = glm::lookAt(transform.GetPosition(),
                       transform.GetPosition() + m_camerafront, m_cameraup);
  return m_view;
}

void
Camera::MoveForward(float val)
{
  transform.SetPosition(transform.GetPosition() +
                        val * m_cameraspeed * m_camerafront);
}

void
Camera::MoveSide(float val)
{
  transform.SetPosition(
    transform.GetPosition() +
    val * glm::normalize(glm::cross(m_camerafront, m_cameraup)) *
      m_cameraspeed);
}

void
Camera::MoveUp(float val)
{
  transform.SetPosition(transform.GetPosition() +
                        val * m_cameraspeed * m_cameraup);
}

void
Camera::InputHandler(Input& input, float deltaTime)
{
  const float cameraSpeed = 2.5f * deltaTime;
  if (input.IsKeyPressed(KeyCode::W))
    MoveForward(1);
  if (input.IsKeyPressed(KeyCode::S))
    MoveForward(-1);
  if (input.IsKeyPressed(KeyCode::A))
    MoveSide(-1);
  if (input.IsKeyPressed(KeyCode::D))
    MoveSide(1);
  if (input.IsKeyPressed(KeyCode::LeftShift))
    MoveUp(-1);
  if (input.IsKeyPressed(KeyCode::Space))
    MoveUp(1);

  double delta_x, delta_y;
  float sensitivity = 2.5f * deltaTime;
  input.GetMouseDelta(&delta_x, &delta_y);
  delta_x *= sensitivity;
  delta_y *= sensitivity;
  transform.m_rotation.x += delta_y;
  transform.m_rotation.y += delta_x;
  if (transform.m_rotation.x > 89.0f)
    transform.m_rotation.x = 89.0f;
  if (transform.m_rotation.x < -89.0f)
    transform.m_rotation.x = -89.0f;
}