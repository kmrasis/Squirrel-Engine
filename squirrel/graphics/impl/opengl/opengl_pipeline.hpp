#include "pipeline.h"
#include "shader.h"

namespace Squirrel::GFX::OpenGL
{
class OpenGLPipeline : public Pipeline
{
public:
  OpenGLPipeline(const Shader* shader)
      : shader_((Shader*)shader)
  {}
  ~OpenGLPipeline()
  {
    Unbind();
    delete shader_;
  }
  virtual void Bind() const override { shader_->Bind(); }
  virtual void Unbind() const override { shader_->Unbind(); }

private:
  Shader* shader_;
};
} // namespace Squirrel::GFX::OpenGL
