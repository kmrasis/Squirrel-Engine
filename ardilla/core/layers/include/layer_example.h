#include "layer.h"

namespace Squirrel::GFX
{
class Mesh;
class Pipeline;
} // namespace Squirrel::GFX
class ExampleLayer : public Squirrel::Layer
{
public:
  ExampleLayer();
  ~ExampleLayer();
  void Attach() override;
  void Detach() override;
  void Update(const float& delta_time_s) override;
  void Render() override;
  void ImGuiRender() override;
  void HandleEvent(const std::shared_ptr<Squirrel::Event> event) override;

private:
  Squirrel::GFX::Mesh* mesh_;
  Squirrel::GFX::Pipeline* pipeline_;
};
