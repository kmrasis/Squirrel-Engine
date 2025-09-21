#pragma once

#include <glm/glm.hpp>
#include <string>

namespace Squirrel::GFX
{
enum class API;

class Shader
{
public:
  Shader()          = default;
  virtual ~Shader() = default;

  virtual void Bind() const   = 0;
  virtual void Unbind() const = 0;

  virtual void UploadUniformInt(const std::string& name, const int& i) {}
  virtual void UploadUniformFloat(const std::string& name, const float& f) {}
  virtual void UploadUniformFloat2(const std::string& name, const ::glm::vec2& vec) {}
  virtual void UploadUniformFloat3(const std::string& name, const ::glm::vec3& vec) {}
  virtual void UploadUniformFloat4(const std::string& name, const ::glm::vec4& vec) {}
  virtual void UploadUniformMat2(const std::string& name, const ::glm::mat2& matrix) {}
  virtual void UploadUniformMat3(const std::string& name, const ::glm::mat3& matrix) {}
  virtual void UploadUniformMat4(const std::string& name, const ::glm::mat4& matrix) {}
};
} // namespace Squirrel::GFX
