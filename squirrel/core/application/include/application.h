#pragma once

#include <memory>

namespace Squirrel
{
namespace GFX
{
  class Renderer;
}
class WindowManager;
class EventManager;
class LayerStack;
class Layer;
class DebugLayer;
class OrthoCamera;
class Application
{
public:
  Application();
  virtual ~Application();

  void Run();
  void PushLayer(Layer* layer);
  void PushOverlay(Layer* layer);

private:
  bool is_initialised_ = false;
  std::unique_ptr<WindowManager> window_manager_;
  std::unique_ptr<EventManager> event_manager_;
  std::unique_ptr<LayerStack> layer_stack_;
  std::unique_ptr<GFX::Renderer> renderer_;
  std::unique_ptr<OrthoCamera> camera_;
  DebugLayer* debug_layer_;
};

// To be defined in client
Application* CreateApplication();
} // namespace Squirrel
