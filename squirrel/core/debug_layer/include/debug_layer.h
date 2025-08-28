#pragma once
#include "layer.h"

struct GLFWwindow;
namespace Squirrel
{
class KeyPressEvent;
class KeyTypeEvent;
class WindowFocusEvent;
;
class MouseButtonEvent;
class MouseMoveEvent;
class MouseScrollEvent;
class Shader;
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
  void ProcessKeyPressEvent(const std::shared_ptr<KeyPressEvent> key_press_event);
  void ProcessKeyTypeEvent(const std::shared_ptr<KeyTypeEvent> key_type_event);
  void ProcessWindowFocusEvent(const std::shared_ptr<WindowFocusEvent> window_focus_event);
  void ProcessMouseButtonEvent(const std::shared_ptr<MouseButtonEvent> mouse_button_event);
  void ProcessMouseMoveEvent(const std::shared_ptr<MouseMoveEvent> mouse_move_event);
  void ProcessMouseScrollEvent(const std::shared_ptr<MouseScrollEvent> mouse_scroll_event);
  bool IsInitialised() { return is_initialised_; }

private:
  bool is_initialised_  = false;
  ::GLFWwindow* window_ = nullptr;
  static std::shared_ptr<Shader> shader_;
};
} // namespace Squirrel
