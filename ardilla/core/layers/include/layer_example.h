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
  void Update() override;
  void Render() override;
  void ImGuiRender() override;
  void HandleEvent(const std::shared_ptr<Squirrel::Event> event) override;

private:
  float vertices[24] = {
      // pos              // color
      -0.5f, 0.5f,  0.0f, 1.0f, 0.0f, 0.0f, // 0
      0.5f,  0.5f,  0.0f, 1.0f, 1.0f, 0.0f, // 1
      0.5f,  -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, // 2
      -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, // 3
  };

  int indices[6] = {0, 1, 2, 2, 3, 0};
  float del      = 0.01f;
  Squirrel::GFX::Mesh* mesh_;
  Squirrel::GFX::Pipeline* pipeline_;
};
