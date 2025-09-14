#include <glm/glm.hpp>

namespace Squirrel
{
class OrthoCamera
{
public:
  OrthoCamera(float left, float right, float bottom, float top);
  ~OrthoCamera();

  void SetPosition(const ::glm::vec3& position);
  void SetRotation(const float& rotation);
  const ::glm::vec3& GetPosition();
  const float& GetRotation();

  const ::glm::mat4& GetProjectionMatrix();
  const ::glm::mat4& GetViewMatrix();
  const ::glm::mat4& GetViewProjectionMatrix();

private:
  void UpdateMatrices();

private:
  ::glm::vec3 position_;
  float rotation_;
  ::glm::mat4 projection_matrix_;
  ::glm::mat4 view_matrix_;
  ::glm::mat4 view_projection_matrix_;
};
} // namespace Squirrel
