#pragma once

#include <cstddef>
namespace Squirrel::GFX
{
enum class BufferType
{
  Vertex,
  Index,
  Uniform,
  Storage
};

enum class BufferUsage
{
  Static,
  Dynamic,
  Stream
};

class Buffer
{
public:
  Buffer()          = default;
  virtual ~Buffer() = default;

  virtual void Bind() const   = 0;
  virtual void Unbind() const = 0;

  virtual void Update(const BufferType& type, const BufferUsage& usage, const void* data, const size_t& size) = 0;
};
} // namespace Squirrel::GFX
