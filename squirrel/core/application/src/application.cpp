#include "application.h"
#include "log-impl.h"

#include "debug_layer.h"
#include "event_manager.h"
#include "input_poller.h"
#include "layerstack.h"
#include "renderer.h"

namespace Squirrel
{

Application::Application(){};
Application::~Application(){};

void Application::Init()
{
  ::Utils::Logger::Init();

  layer_stack_ = std::make_unique<LayerStack>();
  layer_stack_->Init();

  event_manager_ = std::make_unique<EventManager>(*layer_stack_);
  event_manager_->Init();
  if (!event_manager_->IsInitialised()) // Check if glfw/glad are initialised
  {
    CONSOLE_ERROR("Failed to initialise Squirrel Engine");
    return;
  }

  DebugLayer* debug_layer = new DebugLayer;
  layer_stack_->PushOverlay(debug_layer);
  renderer_ = std::make_unique<Renderer>(event_manager_->GetWindowRef(), *layer_stack_, *debug_layer);
  renderer_->Init();
  if (!renderer_->IsInitialised()) // Check if ImGui is initialised
  {
    CONSOLE_ERROR("Failed to initialise Squirrel Engine");
    return;
  }

  is_initialised_ = true;
  CONSOLE_INFO("Initialised Squirrel Engine successfully");
}

void Application::DeInit()
{
  CONSOLE_INFO("DeInitialising Squirrel Engine");
  renderer_->DeInit();
  event_manager_->DeInit();
  layer_stack_->DeInit();
  ::Utils::Logger::DeInit();
  is_initialised_ = false;
}

void Application::Run()
{
  CONSOLE_INFO("Booting up the Squirrel Engine!");

  InputPoller& input_poller = InputPoller::GetInputPoller();
  while (is_initialised_ && event_manager_->IsRunning())
  {
    event_manager_->DispatchEvents();
    layer_stack_->Update();

    renderer_->StartNewFrame();
    renderer_->RenderLayers();
    renderer_->ImGuiRenderLayers();
    renderer_->DrawImGuiLayerFrame();
    renderer_->SwapBuffers();
    CONSOLE_INFO("'A' key pressed: [{}]", input_poller.IsKeyPressed(65));
    CONSOLE_INFO("Mouse at: [{}, {}]", input_poller.GetCursorX(), input_poller.GetCursorY());
  }
}

void Application::PushLayer(Layer* layer) { layer_stack_->PushLayer(layer); }
void Application::PushOverlay(Layer* layer) { layer_stack_->PushOverlay(layer); }
} // namespace Squirrel
