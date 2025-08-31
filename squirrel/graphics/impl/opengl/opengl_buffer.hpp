#include "buffer.h"
#include "glad/glad.h"

namespace Squirrel::GFX::OpenGL
{
class OpenGLBuffer : public Buffer
{
public:
  OpenGLBuffer(const BufferType& type, const BufferUsage& usage, const void* data, const size_t& size)
      : type_(BufferTypeToGLenum(type)),
        usage_(BufferUsageToGLenum(usage)),
        data_((GLfloat*)data),
        size_(size)
  {
    CreateNewBuffer();
  }
  ~OpenGLBuffer()
  {
    DeleteCurrBuffer();
    Unbind();
  }

  void Bind() const override { glBindBuffer(type_, buffer_id_); }
  void Unbind() const override { glBindBuffer(type_, 0); }
  void Update(const BufferType& type, const BufferUsage& usage, const void* data, const size_t& size) override
  {
    DeleteCurrBuffer();
    type_  = BufferTypeToGLenum(type);
    usage_ = BufferUsageToGLenum(usage);
    data_  = (GLfloat*)data;
    size_  = size;
    CreateNewBuffer();
  }

private:
  void DeleteCurrBuffer() { glDeleteBuffers(1, &buffer_id_); }
  void CreateNewBuffer()
  {
    glGenBuffers(1, &buffer_id_);
    Bind();
    glBufferData(type_, size_, data_, usage_);
  }
  inline GLenum BufferTypeToGLenum(const BufferType& type) const
  {
    switch (type)
    {
      case BufferType::Vertex:
        return GL_ARRAY_BUFFER;
      case BufferType::Index:
        return GL_ELEMENT_ARRAY_BUFFER;
      case BufferType::Uniform:
        return GL_UNIFORM_BUFFER;
      case BufferType::Storage:
        return GL_SHADER_STORAGE_BUFFER;
    }
  }
  inline GLenum BufferUsageToGLenum(const BufferUsage& usage) const
  {
    switch (usage)
    {
      case BufferUsage::Static:
        return GL_STATIC_DRAW;
      case BufferUsage::Dynamic:
        return GL_DYNAMIC_DRAW;
      case BufferUsage::Stream:
        return GL_STREAM_DRAW;
    }
  }
  GLuint buffer_id_;
  GLenum type_;
  GLenum usage_;
  GLfloat* data_;
  GLsizei size_;
};
} // namespace Squirrel::GFX::OpenGL
