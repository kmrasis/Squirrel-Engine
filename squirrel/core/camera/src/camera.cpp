#include "camera.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Squirrel
{
OrthoCamera::OrthoCamera(float left, float right, float bottom, float top)
    : position_(::glm::vec3(0.0f, 0.0f, 0.0f)),
      rotation_(0.0f),
      projection_matrix_(::glm::ortho(left, right, bottom, top)),
      view_matrix_(::glm::mat4(1.0f)),
      view_projection_matrix_(projection_matrix_ * view_matrix_)
{}
OrthoCamera::~OrthoCamera() = default;

void OrthoCamera::UpdateMatrices()
{
  ::glm::mat4 transform = ::glm::rotate(::glm::mat4(1.0f), rotation_, ::glm::vec3(0, 0, 1))
                        * ::glm::translate(::glm::mat4(1.0f), position_);

  view_matrix_            = ::glm::inverse(transform);
  view_projection_matrix_ = projection_matrix_ * view_matrix_;
}

void OrthoCamera::SetPosition(const ::glm::vec3& position)
{
  position_ = position;
  UpdateMatrices();
}
void OrthoCamera::SetRotation(const float& rotation)
{
  rotation_ = rotation;
  UpdateMatrices();
}
void OrthoCamera::SetPositionAndRotation(const ::glm::vec3& position, const float& rotation)
{
  position_ = position;
  rotation_ = rotation;
  UpdateMatrices();
}
const ::glm::vec3& OrthoCamera::GetPosition() { return position_; }
const float& OrthoCamera::GetRotation() { return rotation_; }

const ::glm::mat4& OrthoCamera::GetProjectionMatrix() { return projection_matrix_; }
const ::glm::mat4& OrthoCamera::GetViewMatrix() { return view_matrix_; }
const ::glm::mat4& OrthoCamera::GetViewProjectionMatrix() { return view_projection_matrix_; }
} // namespace Squirrel
