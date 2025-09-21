#pragma once

#include <cstddef>
#include <cstdint>
#include <vector>
namespace Squirrel::GFX
{
enum class DataType
{
  Bool,

  // Ints
  Int,
  Int2,
  Int3,
  Int4,

  // Floats
  Float,
  Float2,
  Float3,
  Float4,

  // Mats
  Mat2,
  Mat3,
  Mat4
};
static int32_t GetCount(const DataType& type)
{
  switch (type)
  {
    case DataType::Bool:
    case DataType::Int:
    case DataType::Float:
      return 1;

    case DataType::Int2:
    case DataType::Float2:
      return 2;

    case DataType::Int3:
    case DataType::Float3:
      return 3;

    case DataType::Int4:
    case DataType::Float4:
    case DataType::Mat2:
      return 4;

    case DataType::Mat3:
      return 9;

    case DataType::Mat4:
      return 16;
  }
  return 0;
}

static size_t GetBytes(const DataType& type)
{
  switch (type)
  {
    case DataType::Bool:
      return sizeof(bool);

    case DataType::Int:
    case DataType::Int2:
    case DataType::Int3:
    case DataType::Int4:
      return sizeof(int) * GetCount(type);

    case DataType::Float:
    case DataType::Float2:
    case DataType::Float3:
    case DataType::Float4:

    case DataType::Mat2:
    case DataType::Mat3:
    case DataType::Mat4:
      return sizeof(float) * GetCount(type);
  }
  return 0;
}

struct VertexAttribute
{
  VertexAttribute(uint32_t loc, size_t offbytes, int32_t cnt)
      : location(loc),
        offsetbytes(offbytes),
        count(cnt)
  {}
  uint32_t location;
  size_t offsetbytes;
  int32_t count;
};

class VertexLayout
{
public:
  VertexLayout(std::initializer_list<DataType> types)
  {
    stridebytes       = 0;
    uint32_t location = 0;
    for (auto& type : types)
    {
      attributes_.emplace_back(location, stridebytes, GetCount(type));
      ++location;
      stridebytes += GetBytes(type);
    }
  }
  ~VertexLayout() = default;
  const std::vector<VertexAttribute>& GetAttributes() const { return attributes_; }

  size_t stridebytes;

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
