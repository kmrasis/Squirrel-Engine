#include "Config.h"

#ifdef SQUIRREL_USE_OPENGL
#include "opengl_shader.h"
#endif

namespace Squirrel
{
Shader::Shader()  = default;
Shader::~Shader() = default;
std::shared_ptr<Shader> Shader::CreateShader(const char* vertex_src, const char* fragment_src)
{
#ifdef SQUIRREL_USE_OPENGL
  return std::make_shared<OpenGLShader>(vertex_src, fragment_src);
#else
  return nullptr;
#endif
}
} // namespace Squirrel
