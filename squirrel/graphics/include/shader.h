#pragma once

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
};
} // namespace Squirrel::GFX
