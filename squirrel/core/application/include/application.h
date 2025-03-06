#pragma once

#include <memory>

namespace Squirrel
{
class Event;
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

  void DispatchEventToLayers(const std::shared_ptr<Event> event);

  void PushLayer(Layer* layer);
  void PushOverlay(Layer* layer);

private:
  bool is_running = false;
  std::unique_ptr<EventManager> event_manager_;
  std::unique_ptr<LayerStack> layer_stack_;
};

// To be defined in client
Application* CreateApplication();
} // namespace Squirrel
