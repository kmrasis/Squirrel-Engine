#include "opengl_shader.h"

namespace Squirrel
{
Shader::Shader()  = default;
Shader::~Shader() = default;
std::shared_ptr<Shader> Shader::CreateShader(const char* vertex_src, const char* fragment_src)
{
  return std::make_shared<OpenGLShader>(vertex_src, fragment_src);
}
} // namespace Squirrel
