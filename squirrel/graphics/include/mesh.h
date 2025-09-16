#pragma once

#include <cstddef>
#include <cstdint>
#include <vector>
namespace Squirrel::GFX
{
struct VertexAttribute
{
  uint32_t location;
  size_t offset;
  uint32_t size;
};

class VertexLayout
{
public:
  VertexLayout(const uint32_t& stride)
      : stride(stride)
  {}
  ~VertexLayout() = default;

  void AddAttribute(const uint32_t& location, const size_t& offset, const uint32_t& size)
  {
    attributes_.emplace_back(VertexAttribute{location, offset, size});
  }
  const std::vector<VertexAttribute>& GetAttributes() const { return attributes_; }

  uint32_t stride;

private:
  std::vector<VertexAttribute> attributes_;
};

class Mesh
{
public:
  Mesh()          = default;
  virtual ~Mesh() = default;

  virtual void Bind() const   = 0;
  virtual void Unbind() const = 0;
  virtual void Draw() const   = 0;

  virtual uint32_t GetVertexCount() const = 0;
  virtual uint32_t GetIndexCount() const  = 0;
};
} // namespace Squirrel::GFX
