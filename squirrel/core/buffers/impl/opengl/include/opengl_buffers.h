#include "buffers.h"

using GLuint = unsigned int;
namespace Squirrel
{
class OpenGLVertexBuffer : public VertexBuffer
{
public:
  OpenGLVertexBuffer(float* vertices, unsigned int count);
  ~OpenGLVertexBuffer();
  virtual void Bind() const override;
  virtual void Unbind() const override;

private:
  GLuint VBO;
};

class OpenGLIndexBuffer : public IndexBuffer
{
public:
  OpenGLIndexBuffer(unsigned int* indices, unsigned int count);
  ~OpenGLIndexBuffer();
  virtual void Bind() const override;
  virtual void Unbind() const override;

private:
  GLuint EBO;
};
} // namespace Squirrel
