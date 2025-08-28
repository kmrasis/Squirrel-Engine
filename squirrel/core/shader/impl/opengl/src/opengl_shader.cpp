#include "opengl_shader.h"
#include "log-impl.h"

#include "glad/glad.h"

#include "fragment_shader_src.h"
#include "vertex_shader_src.h"

namespace Squirrel
{
OpenGLShader::OpenGLShader(const char* vertex_src, const char* fragment_src)
{
  // Create and compile vertex shader
  GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader, 1, (vertex_src != nullptr) ? &vertex_src : &vertexShaderSource, NULL);
  glCompileShader(vertexShader);
  checkCompileErrors(vertexShader, true);

  // Create and compile fragment shader
  GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, (fragment_src != nullptr) ? &fragment_src : &fragmentShaderSource, NULL);
  glCompileShader(fragmentShader);
  checkCompileErrors(fragmentShader, true);

  // Create a shader program and attach vertex and fragment shaders to it.
  shader_program_ = glCreateProgram();
  glAttachShader(shader_program_, vertexShader);
  glAttachShader(shader_program_, fragmentShader);
  glLinkProgram(shader_program_);
  checkCompileErrors(shader_program_, false);

  // Delete now useless shaders
  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);
}
OpenGLShader::~OpenGLShader() { glDeleteProgram(shader_program_); }

void OpenGLShader::Bind() const { glUseProgram(shader_program_); }
void OpenGLShader::Unbind() const { glUseProgram(0); }

// Error checking helper
void OpenGLShader::checkCompileErrors(unsigned int shader, bool is_shader)
{
  GLint success;
  GLchar infoLog[1024];
  if (is_shader)
  {
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
      glGetShaderInfoLog(shader, 1024, NULL, infoLog);
      LOG_ERROR("Shader Compilation Error:\n", infoLog);
    }
  } else
  {
    glGetProgramiv(shader, GL_LINK_STATUS, &success);
    if (!success)
    {
      glGetProgramInfoLog(shader, 1024, NULL, infoLog);
      LOG_ERROR("Program Linking Error:\n", infoLog);
    }
  }
}
} // namespace Squirrel
