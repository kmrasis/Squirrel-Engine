#include "buffer.h"
#include "mesh.h"

#include "glad/glad.h"

namespace Squirrel::GFX::OpenGL
{
class OpenGLMesh : public Mesh
{
public:
  OpenGLMesh(Buffer* vtx_buffer, const VertexLayout& vtx_layout, const uint32_t& vtx_count, Buffer* idx_buffer,
             const uint32_t& idx_count)
      : vtx_buffer_(vtx_buffer),
        vtx_layout_(vtx_layout),
        vtx_count_(vtx_count),
        idx_buffer_(idx_buffer),
        idx_count_(idx_count)
  {
    glGenVertexArrays(1, &id_);
    Bind();
    vtx_buffer_->Bind();
    for (const auto& attr : vtx_layout_.GetAttributes())
    {
      glVertexAttribPointer((GLuint)attr.location,
                            (GLint)attr.count,
                            GL_FLOAT,
                            GL_FALSE,
                            (GLsizei)vtx_layout_.stridebytes,
                            (void*)attr.offsetbytes);
      glEnableVertexAttribArray((GLuint)attr.location);
    }

    if (idx_buffer_)
    {
      idx_buffer_->Bind();
    }
    Unbind();
    vtx_buffer_->Unbind();
  }
  ~OpenGLMesh()
  {
    Unbind();
    delete vtx_buffer_;
    delete idx_buffer_;
  }

  virtual void Bind() const override { glBindVertexArray(id_); }
  virtual void Unbind() const override { glBindVertexArray(0); }
  virtual uint32_t GetVertexCount() const override { return vtx_count_; }
  virtual uint32_t GetIndexCount() const override { return idx_count_; }
  virtual void Draw() const override
  {
    Bind();
    if (idx_buffer_)
    {
      glDrawElements(GL_TRIANGLES, (GLsizei)(3 * idx_count_), GL_UNSIGNED_INT, nullptr);
    } else
    {
      glDrawArrays(GL_TRIANGLES, 0, vtx_count_);
    }
    Unbind();
  }

private:
  Buffer* vtx_buffer_;
  VertexLayout vtx_layout_;
  uint32_t vtx_count_;
  Buffer* idx_buffer_;
  uint32_t idx_count_;
  GLuint id_;
};
} // namespace Squirrel::GFX::OpenGL
