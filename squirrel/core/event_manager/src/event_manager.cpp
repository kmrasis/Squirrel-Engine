#include "event_manager.h"
#include "log-impl.h"

#include "event.h"
#include "layer.h"
#include "layerstack.h"
#include "window_manager.h"

namespace Squirrel
{
EventManager::EventManager(WindowManager* window_manager, LayerStack* layerstack)
    : window_manager_(window_manager),
      layerstack_(layerstack)
{
  window_manager_->SetEventCallbacks();
  CONSOLE_INFO("Initialised Event Manager successfully");
}
EventManager::~EventManager() { CONSOLE_INFO("DeInitialised Event Manager successfully"); }

void EventManager::DispatchEvents()
{
  auto pending_event_queue = window_manager_->GetEventQueue();
  LOG_DEBUG("Received total events: [{}]", pending_event_queue->size());
  while (pending_event_queue->size())
  {
    std::shared_ptr<Event> event = pending_event_queue->front();
    pending_event_queue->pop();
    for (auto it = layerstack_->rbegin(); it != layerstack_->rend(); ++it)
    {
      auto& layer = *it;
      LOG_TRACE("Sending {} event to {} layer", event->GetEventName(), layer->GetName());
      layer->HandleEvent(event);
      if (event->IsHandled())
        break;
    }
  }
}
} // namespace Squirrel
