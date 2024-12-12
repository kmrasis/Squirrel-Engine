#pragma once

#include <memory>

namespace Squirrel
{
class EventManager;
class Application
{
public:
  Application();
  virtual ~Application();

  void Init();
  void DeInit();

  void Run();

private:
  bool is_running = false;
  std::unique_ptr<EventManager> event_manager_;
};

// To be defined in client
Application* CreateApplication();
} // namespace Squirrel
