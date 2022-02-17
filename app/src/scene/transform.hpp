#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Transform
{
public:
  Transform(glm::vec3 pos = glm::vec3(0.0f), glm::vec3 rot = glm::vec3(0.0f),
            glm::vec3 scale = glm::vec3(1.0f))
    : m_position(pos)
    , m_rotation(rot)
    , m_scale(scale)
  {
  }

  ~Transform() = default;

  glm::vec3 GetPosition() { return m_position; };
  glm::vec3 GetRotation() { return m_rotation; };
  glm::vec3 GetScale() { return m_scale; };

  void SetPosition(glm::vec3 value) { m_position = value; };
  void SetRotation(glm::vec3 value) { m_rotation = value; };
  void SetScale(glm::vec3 value) { m_scale = value; };

public:
  glm::vec3 m_position;
  glm::vec3 m_rotation;
  glm::vec3 m_scale;
};