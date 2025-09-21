#include "Config.h"

#ifdef SQUIRREL_USE_OPENGL
#include "opengl_renderer.h"
#endif
#include "device.h"
#include "shader.h"

namespace Squirrel::GFX
{
Renderer::Renderer() = default;
Renderer::~Renderer() { Device::ResetDefaults(); }
Renderer* Renderer::CreateRenderer(const API& api)
{
  Device::SetAPI(api);
  switch (Device::GetAPI())
  {
    case API::OpenGL:
#ifdef SQUIRREL_USE_OPENGL
      return new OpenGLRenderer();
#else
      return nullptr;
#endif
      break;

    default:
      break;
  }
  return nullptr;
}
void Renderer::UpdateDefaultShaderViewProjectionMatrix(const ::glm::mat4& matrix)
{
  Shader* default_shader = Device::GetDefaultShader();
  if (default_shader)
  {
    default_shader->Bind();
    default_shader->UploadUniformMat4("viewProjectionMatrix", matrix);
    default_shader->Unbind();
  }
}
} // namespace Squirrel::GFX
