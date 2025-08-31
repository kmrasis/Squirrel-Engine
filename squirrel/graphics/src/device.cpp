#include "device.h"

#include "opengl_buffer.hpp"
#include "opengl_mesh.hpp"
#include "opengl_pipeline.hpp"
#include "opengl_shader.hpp"

namespace Squirrel::GFX
{
API Device::api_ = API::None;

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
} // namespace Squirrel::GFX
