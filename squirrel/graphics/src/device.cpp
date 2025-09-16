#include "device.h"

#include "opengl_buffer.hpp"
#include "opengl_mesh.hpp"
#include "opengl_pipeline.hpp"
#include "opengl_shader.hpp"

namespace Squirrel::GFX
{
API Device::api_ = API::None;

std::unique_ptr<Shader> Device::default_shader_     = nullptr;
std::unique_ptr<Pipeline> Device::default_pipeline_ = nullptr;

API Device::GetAPI() { return api_; }
void Device::SetAPI(const API& api)
{
  if (api_ == API::None)
  {
    api_ = api;
  } else
  {
    CONSOLE_ERROR("Runtime API change is not allowed.");
  }
  default_shader_.reset();
  default_pipeline_.reset();
}

void Device::InitDefaults()
{
  switch (api_)
  {
    case API::OpenGL:
      default_shader_.reset(new OpenGL::OpenGLShader(nullptr, nullptr));
      default_pipeline_.reset(new OpenGL::OpenGLPipeline(default_shader_.get()));
      break;

    default:
      break;
  }
}

void Device::ResetDefaults()
{
  default_shader_.reset();
  default_pipeline_.reset();
}

Buffer* Device::CreateBuffer(const BufferType& type, const BufferUsage& usage, const void* data, size_t size)
{
  switch (api_)
  {
    case API::OpenGL:
      return new OpenGL::OpenGLBuffer(type, usage, data, size);
  }
  CONSOLE_ERROR("Unknown API type. Failed to create Buffer");
  return nullptr;
}

Shader* Device::CreateShader(const char* vertex_src, const char* fragment_src)
{
  if (!vertex_src && !fragment_src)
  {
    if (!Device::default_shader_)
      InitDefaults();
    return Device::default_shader_.get();
  }
  switch (api_)
  {
    case API::OpenGL:
      return new OpenGL::OpenGLShader(vertex_src, fragment_src);
  }
  CONSOLE_ERROR("Unknown API type. Failed to create Shader");
  return nullptr;
}

Pipeline* Device::CreatePipeline(const Shader* shader)
{
  if (!shader)
  {
    if (!default_pipeline_)
      InitDefaults();
    return Device::default_pipeline_.get();
  }
  switch (api_)
  {
    case API::OpenGL:
      return new OpenGL::OpenGLPipeline(shader);
  }
  CONSOLE_ERROR("Unknown API type. Failed to create Pipeline");
  return nullptr;
}

Mesh* Device::CreateMesh(Buffer* vtx_buffer, const VertexLayout& vtx_layout, const uint32_t& vtx_count,
                         Buffer* idx_buffer, const uint32_t& idx_count)
{
  switch (api_)
  {
    case API::OpenGL:
      return new OpenGL::OpenGLMesh(vtx_buffer, vtx_layout, vtx_count, idx_buffer, idx_count);
  }
  CONSOLE_ERROR("Unknown API type. Failed to create Mesh");
  return nullptr;
}
Shader* Device::GetDefaultShader()
{
  if (default_shader_)
  {
    return default_shader_.get();
  }
  return nullptr;
}
} // namespace Squirrel::GFX
