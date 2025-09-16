#include "renderer.h"

namespace Squirrel::GFX
{
class OpenGLRenderer : public Renderer
{
public:
  OpenGLRenderer();
  ~OpenGLRenderer();

  virtual void StartNewFrame(const int& width, const int& height) override;
};
} // namespace Squirrel::GFX
