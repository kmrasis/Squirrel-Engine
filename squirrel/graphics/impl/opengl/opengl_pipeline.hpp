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
  ~OpenGLPipeline() {}
  virtual void Bind() const override { shader_->Bind(); }
  virtual void Unbind() const override { shader_->Unbind(); }
  virtual Shader* GetShader() const override { return shader_; }

private:
  Shader* shader_;
};
} // namespace Squirrel::GFX::OpenGL
