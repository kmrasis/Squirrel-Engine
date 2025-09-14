#pragma once

#include <memory>

namespace Squirrel
{
class GraphicsContext;
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
  std::unique_ptr<GraphicsContext> graphics_context_;
  std::unique_ptr<OrthoCamera> camera_;
  DebugLayer* debug_layer_;
};

// To be defined in client
Application* CreateApplication();
} // namespace Squirrel
