#pragma once

#include <memory>

namespace Squirrel
{
class Renderer;
class EventManager;
class LayerStack;
class Layer;
class Application
{
public:
  Application();
  virtual ~Application();

  void Init();
  void DeInit();

  void Run();
  void PushLayer(Layer* layer);
  void PushOverlay(Layer* layer);

private:
  bool is_initialised_ = false;
  std::unique_ptr<EventManager> event_manager_;
  std::unique_ptr<LayerStack> layer_stack_;
  std::unique_ptr<Renderer> renderer_;
};

// To be defined in client
Application* CreateApplication();
} // namespace Squirrel
