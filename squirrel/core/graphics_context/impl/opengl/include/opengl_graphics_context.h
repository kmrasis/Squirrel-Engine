#include "graphics_context.h"

namespace Squirrel
{
class OpenGLGraphicsContext : public GraphicsContext
{
public:
  OpenGLGraphicsContext();
  ~OpenGLGraphicsContext();

  virtual void StartNewFrame(const int& width, const int& height) override;
};
} // namespace Squirrel
