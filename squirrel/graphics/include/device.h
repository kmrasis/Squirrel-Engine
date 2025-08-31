#pragma once

#include <cstddef>
#include <cstdint>
namespace Squirrel::GFX
{

class Buffer;
class Shader;
class Pipeline;
class Mesh;
class VertexLayout;

enum class BufferType;
enum class BufferUsage;

enum class API
{
  None,
  OpenGL
};

class Device
{
public:
  static void SetAPI(const API& api);
  static API GetAPI();
  static Buffer* CreateBuffer(const BufferType& type, const BufferUsage& usage, const void* data, size_t size);
  static Shader* CreateShader(const char* vertex_src, const char* fragment_src);
  static Pipeline* CreatePipeline(const Shader* shader);
  static Mesh* CreateMesh(Buffer* vtx_buffer, const VertexLayout& vtx_layout, const uint32_t& vtx_count,
                          Buffer* idx_buffer, const uint32_t& idx_count);

private:
  static API api_;
};

} // namespace Squirrel::GFX