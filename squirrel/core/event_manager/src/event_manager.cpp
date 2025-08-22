#include "event_manager.h"
#include "log-impl.h"

#include "event.h"
#include "layer.h"
#include "layerstack.h"
#include "window_manager.h"
#include "window_property.h"

namespace Squirrel
{
EventManager::EventManager(LayerStack& layerstack)
    : layerstack_(layerstack)
{}
EventManager::~EventManager() {}

void EventManager::Init()
{
  // Initialise Window Manager to start getting events
  window_manager_ = std::make_unique<WindowManager>();
  window_manager_->Init();

  if (!window_manager_->IsInitialised())
  {
    CONSOLE_ERROR("Failed to initialise Event Manager");
    return;
  }

  WindowProperty window_props = {"Squirrel Engine", true, 0, 0, 600, 800};
  window_manager_->CreateWindow(window_props);
  is_initialised_ = true;
  CONSOLE_INFO("Initialised Event Manager successfully");
}

WindowManager& EventManager::GetWindowRef() { return *window_manager_; }

void EventManager::DeInit()
{
  window_manager_->DeInit();
  is_initialised_ = false;
  CONSOLE_INFO("DeInitialised Event Manager successfully");
}

bool EventManager::IsRunning() { return is_initialised_ && !window_manager_->ShouldWindowClose(); }

void EventManager::DispatchEvents()
{
  window_manager_->PollEvents();

  auto& pending_event_queue = window_manager_->GetEventQueue();
  LOG_DEBUG("Received total events: [{}]", pending_event_queue.size());
  while (pending_event_queue.size())
  {
    std::shared_ptr<Event> event = pending_event_queue.front();
    pending_event_queue.pop();
    for (auto it = layerstack_.end(); it != layerstack_.begin();)
    {
      auto& layer = *--it;
      LOG_TRACE("Sending {} event to {} layer", event->GetEventName(), layer->GetName());
      layer->HandleEvent(event);
      if (event->IsHandled())
        break;
    }
  }
}
} // namespace Squirrel
