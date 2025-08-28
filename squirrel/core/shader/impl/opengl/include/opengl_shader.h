#include "shader.h"

namespace Squirrel
{
class OpenGLShader : public Shader
{
public:
  OpenGLShader(const char* vertex_src, const char* fragment_src);
  ~OpenGLShader();

  virtual void Bind() const override;
  virtual void Unbind() const override;
  void checkCompileErrors(unsigned int shader, bool is_shader = true);

private:
  unsigned int shader_program_;
};
} // namespace Squirrel
