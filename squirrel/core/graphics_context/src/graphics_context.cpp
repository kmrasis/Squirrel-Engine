#include "Config.h"

#ifdef SQUIRREL_USE_OPENGL
#include "opengl_graphics_context.h"
#endif

namespace Squirrel
{
GraphicsContext::GraphicsContext()  = default;
GraphicsContext::~GraphicsContext() = default;
GraphicsContext* GraphicsContext::CreateGraphicsContext()
{
#ifdef SQUIRREL_USE_OPENGL
  return new OpenGLGraphicsContext();
#else
  return nullptr;
#endif
}
} // namespace Squirrel
