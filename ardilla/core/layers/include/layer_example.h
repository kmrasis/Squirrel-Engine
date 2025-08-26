#include "layer.h"

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
};
