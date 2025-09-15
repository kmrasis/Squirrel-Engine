#include "opengl_renderer.h"
#include "log-impl.h"

#include "glad/glad.h"

namespace Squirrel::GFX
{
OpenGLRenderer::OpenGLRenderer() { CONSOLE_INFO("Using OpenGLRenderer"); }
OpenGLRenderer::~OpenGLRenderer() = default;

void OpenGLRenderer::StartNewFrame(const int& width, const int& height)
{
  LOG_DEBUG("Starting New OpenGLRenderer Frame");

  // Specify viewing area to be used by OpenGL:
  // Bottom Left (0,0) to Top Right (width, Height)
  glViewport(0, 0, width, height);

  // Clear back buffer by assigning new color to it
  glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);
}
} // namespace Squirrel::GFX
