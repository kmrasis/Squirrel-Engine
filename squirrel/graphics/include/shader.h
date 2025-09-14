#pragma once

#include <glm/glm.hpp>

namespace Squirrel::GFX
{
enum class API;

class Shader
{
public:
  Shader()          = default;
  virtual ~Shader() = default;

  virtual void Bind() const                                                      = 0;
  virtual void Unbind() const                                                    = 0;
  virtual void UploadUniform(const std::string& name, const ::glm::mat4& matrix) = 0;
};
} // namespace Squirrel::GFX
