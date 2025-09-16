#include <glm/glm.hpp>
namespace Squirrel::GFX
{
enum class API;
class Device;
class Renderer
{
protected:
  Renderer();

public:
  virtual ~Renderer();
  virtual void StartNewFrame(const int& width, const int& height) = 0;
  static Renderer* CreateRenderer(const API& api);

  void UpdateDefaultShaderViewProjectionMatrix(const ::glm::mat4& matrix);
};
} // namespace Squirrel::GFX
