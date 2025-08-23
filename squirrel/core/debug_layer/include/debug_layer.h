#pragma once
#include "layer.h"

struct GLFWwindow;
namespace Squirrel
{
class DebugLayer : public Layer
{
public:
  DebugLayer();
  ~DebugLayer();
  void Init(void* window);
  void DeInit();
  void StartNewFrame();
  void Attach() override;
  void Detach() override;
  void Update() override;
  void Render() override;
  void ImGuiRender() override;
  void DrawFrame();
  void HandleEvent(const std::shared_ptr<Event> event) override;
  bool IsInitialised() { return is_initialised_; }

private:
  bool is_initialised_  = false;
  ::GLFWwindow* window_ = nullptr;
};
} // namespace Squirrel
