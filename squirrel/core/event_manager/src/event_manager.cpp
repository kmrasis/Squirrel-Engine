#include "event_manager.h"
#include "log-impl.h"

#include "event.h"
#include "window_manager.h"
#include "window_property.h"

namespace Squirrel
{
EventManager::EventManager() {}
EventManager::~EventManager() {}

void EventManager::Init()
{
  // Initialise Window Manager to start getting events
  window_manager_ = std::make_unique<WindowManager>();
  window_manager_->Init();

  if (!window_manager_->IsInitialised())
  {
    CONSOLE_ERROR("Failed to initialised Event Manager");
    return;
  }

  WindowProperty window_props = {"Squirrel Engine", true, 0, 0, 600, 800};
  window_manager_->CreateWindow(window_props);
  is_running = true;
  CONSOLE_INFO("Initialised Event Manager successfully");
}

void EventManager::DeInit()
{
  window_manager_->DeInit();
  is_running = false;
  CONSOLE_INFO("DeInitialised Event Manager successfully");
}

bool EventManager::IsRunning() { return is_running; }

void EventManager::DispatchEvents()
{
  window_manager_->Update();

  /**
   * @todo Implement event handlers to handle different event types
   */

  // Process Events from queue
  if (pending_event_queue_.size())
  {
    std::shared_ptr<Event> event = pending_event_queue_.front();
    pending_event_queue_.pop();
    if (EventType::WindowClose == event->GetEventType())
    {
      window_manager_->CloseWindow();
      is_running = false;
    }
  }
}
} // namespace Squirrel
