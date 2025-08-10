#include "application.h"
#include "log-impl.h"

#include "debug_layer.h"
#include "event.h"
#include "event_manager.h"
#include "layerstack.h"

namespace Squirrel
{

Application::Application(){};
Application::~Application(){};

void Application::Init()
{
  ::Utils::Logger::Init();

  layer_stack_ = std::make_unique<LayerStack>();
  layer_stack_->Init();

  event_manager_ = std::make_unique<EventManager>();
  event_manager_->Init([this](const std::shared_ptr<Event> event) { this->DispatchEventToLayers(event); });
  is_running = true;

  layer_stack_->PushOverlay(new DebugLayer);
  CONSOLE_INFO("Initialised Squirrel Engine successfully");
}

void Application::DeInit()
{
  CONSOLE_INFO("DeInitialising Squirrel Engine");

  layer_stack_->DeInit();
  event_manager_->DeInit();
  ::Utils::Logger::DeInit();
  is_running = false;
}

void Application::Run()
{
  CONSOLE_INFO("Booting up the Squirrel Engine!");
  while (is_running && event_manager_->IsRunning())
  {
    layer_stack_->Update();
    event_manager_->DispatchEvents();
  }
}

void Application::PushLayer(Layer* layer) { layer_stack_->PushLayer(layer); }
void Application::PushOverlay(Layer* layer) { layer_stack_->PushOverlay(layer); }

void Application::DispatchEventToLayers(const std::shared_ptr<Event> event)
{
  for (auto it = layer_stack_->end(); it != layer_stack_->begin();)
  {
    auto& layer = *--it;
    LOG_TRACE("Sending {} event to {} layer", event->GetEventName(), layer->GetName());
    layer->HandleEvent(event);
    if (event->IsHandled())
      break;
  }
}
} // namespace Squirrel
