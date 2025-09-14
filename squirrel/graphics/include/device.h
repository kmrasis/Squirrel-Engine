#pragma once

#include <cstddef>
#include <cstdint>
#include <glm/glm.hpp>
#include <memory>
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

  static void UpdateDefaultShaderViewProjectionMatrix(const ::glm::mat4& matrix);
  static void CleanUp();

private:
  static void InitDefaults();

  static std::unique_ptr<Shader> default_shader_;
  static std::unique_ptr<Pipeline> default_pipeline_;
  static API api_;
};

} // namespace Squirrel::GFX