#include "Config.h"

#ifdef SQUIRREL_USE_OPENGL
#include "opengl_buffers.h"
#endif // SQUIRREL_USE_OPENGL

namespace Squirrel
{
VertexBuffer::VertexBuffer()  = default;
VertexBuffer::~VertexBuffer() = default;
VertexBuffer* VertexBuffer::CreateVertexBuffer(float* vertices, unsigned int count)
{
#ifdef SQUIRREL_USE_OPENGL
  return new OpenGLVertexBuffer(vertices, count);
#else
  return nullptr;
#endif
}

IndexBuffer::IndexBuffer()  = default;
IndexBuffer::~IndexBuffer() = default;
IndexBuffer* IndexBuffer::CreateIndexBuffer(unsigned int* indices, unsigned int count)
{
#ifdef SQUIRREL_USE_OPENGL
  return new OpenGLIndexBuffer(indices, count);
#else
  return nullptr;
#endif
}
} // namespace Squirrel
