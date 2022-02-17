#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "transform.hpp"
#include "input.hpp"

class Camera
{
public:
  Camera(float fov, float aratio, float near, float far);
  ~Camera() = default;

  glm::mat4 GetProjection();
  glm::mat4 GetView();

  void MoveForward(float val);
  void MoveSide(float val);
  void MoveUp(float val);

  void InputHandler(Input& input, float deltaTime);

  Transform transform;

private:
  glm::mat4 m_projection;
  glm::mat4 m_view;

  glm::vec3 m_cameraup;
  glm::vec3 m_camerafront;

  float m_cameraspeed;

  float m_fov;
  float m_ratio;
  float m_near;
  float m_far;
};