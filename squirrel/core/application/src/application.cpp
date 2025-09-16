#include "application.h"
#include "log-impl.h"

#include "camera.h"
#include "debug_layer.h"
#include "event_manager.h"
#include "layerstack.h"
#include "renderer.h"
#include "window_manager.h"

#include "device.h"

namespace Squirrel
{

Application::Application()
{
  ::Utils::Logger::Init();

  window_manager_.reset(WindowManager::CreateManager());
  window_manager_->CreateWindow("Squirrel Engine", 1280, 720);

  layer_stack_   = std::make_unique<LayerStack>();
  event_manager_ = std::make_unique<EventManager>(window_manager_.get(), layer_stack_.get());

  camera_ = std::make_unique<OrthoCamera>(-1.6f, 1.6f, -0.9f, 0.9f);
  renderer_.reset(GFX::Renderer::CreateRenderer(GFX::API::OpenGL));

  debug_layer_ = new DebugLayer();
  debug_layer_->SetWindow(window_manager_->GetRawWindow());
  PushOverlay(debug_layer_);

  is_initialised_ = true;
  CONSOLE_INFO("Initialised Squirrel Engine successfully");
}

Application::~Application()
{
  CONSOLE_INFO("DeInitialising Squirrel Engine");
  renderer_.reset();
  camera_.reset();
  event_manager_.reset();
  layer_stack_.reset();
  window_manager_.reset();
  ::Utils::Logger::DeInit();
  is_initialised_ = false;
}

void Application::Run()
{
  CONSOLE_INFO("Booting up the Squirrel Engine!");
  while (is_initialised_ && !window_manager_->ShouldWindowClose())
  {
    window_manager_->PollEvents();
    event_manager_->DispatchEvents();
    layer_stack_->UpdateLayers();

    int width, height;
    window_manager_->GetWindowSize(&width, &height);
    renderer_->StartNewFrame(width, height);
    debug_layer_->StartNewFrame();

    renderer_->UpdateDefaultShaderViewProjectionMatrix(camera_->GetViewProjectionMatrix());
    layer_stack_->RenderLayers();
    layer_stack_->ImGuiRenderLayers();

    debug_layer_->DrawFrame();
    window_manager_->SwapBuffers();
  }
}

void Application::PushLayer(Layer* layer)
{
  layer->SetCamera(camera_.get());
  layer_stack_->PushLayer(layer);
}
void Application::PushOverlay(Layer* layer)
{
  layer->SetCamera(camera_.get());
  layer_stack_->PushOverlay(layer);
}
} // namespace Squirrel
