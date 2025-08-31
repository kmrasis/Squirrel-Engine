#include "log-impl.h"
#include "shader.h"

#include "glad/glad.h"

#include "default_fragment.h"
#include "default_vertex.h"

namespace Squirrel::GFX::OpenGL
{
class OpenGLShader : public Shader
{
public:
  OpenGLShader(const char* vertex_src, const char* fragment_src)
  {
    // Create and compile vertex shader
    GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader, 1, (vertex_src != nullptr) ? &vertex_src : &default_vertex_src, NULL);
    glCompileShader(vertex_shader);
    checkCompileErrors(vertex_shader, true);

    // Create and compile fragment shader
    GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, 1, (fragment_src != nullptr) ? &fragment_src : &default_fragment_src, NULL);
    glCompileShader(fragment_shader);
    checkCompileErrors(fragment_shader, true);

    // Create a shader program and attach vertex and fragment shaders to it.
    shader_program_ = glCreateProgram();
    glAttachShader(shader_program_, vertex_shader);
    glAttachShader(shader_program_, fragment_shader);
    glLinkProgram(shader_program_);
    checkCompileErrors(shader_program_, false);

    // Delete now useless shaders
    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);
  }
  ~OpenGLShader() { glDeleteProgram(shader_program_); }

  void Bind() const { glUseProgram(shader_program_); }
  void Unbind() const { glUseProgram(0); }

private:
  void checkCompileErrors(GLuint shader, bool is_shader)
  {
    GLint success;
    GLchar infoLog[1024];
    if (is_shader)
    {
      glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
      if (!success)
      {
        glGetShaderInfoLog(shader, 1024, NULL, infoLog);
        CONSOLE_ERROR("Shader Compilation Error: {}", infoLog);
      }
    } else
    {
      glGetProgramiv(shader, GL_LINK_STATUS, &success);
      if (!success)
      {
        glGetProgramInfoLog(shader, 1024, NULL, infoLog);
        CONSOLE_ERROR("Program Linking Error: {}", infoLog);
      }
    }
  }

  GLuint shader_program_;
};
} // namespace Squirrel::GFX::OpenGL
