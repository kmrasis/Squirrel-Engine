#include "renderer.h"
#include "log-impl.h"

#include "debug_layer.h"
#include "layerstack.h"
#include "window_manager.h"

namespace Squirrel
{
Renderer::Renderer(WindowManager& window_manager, LayerStack& layerstack, DebugLayer& debug_layer)
    : window_manager_(window_manager),
      layerstack_(layerstack),
      debug_layer_(debug_layer)
{}
Renderer::~Renderer() {}

void Renderer::Init()
{
  debug_layer_.Init(window_manager_.GetRawWindow());
  if (!debug_layer_.IsInitialised())
  {
    CONSOLE_ERROR("Failed to initialise Renderer");
    return;
  }
  is_initialised_ = true;
  CONSOLE_INFO("Initialised Renderer Successfully");
}
void Renderer::DeInit()
{
  debug_layer_.DeInit();
  is_initialised_ = false;
  CONSOLE_INFO("DeInitialised Renderer Successfully");
}

void Renderer::StartNewFrame()
{
  LOG_DEBUG("Starting New Renderer Frame");
  window_manager_.StartNewFrame();
  debug_layer_.StartNewFrame();
}
void Renderer::RenderLayers()
{
  LOG_DEBUG("Rendering layers")
  for (auto& layer : layerstack_)
  {
    layer->Render();
  }
};
void Renderer::ImGuiRenderLayers()
{
  LOG_DEBUG("ImGui rendering layers")
  for (auto& layer : layerstack_)
  {
    layer->ImGuiRender();
  }
};
void Renderer::DrawImGuiLayerFrame()
{
  LOG_DEBUG("Drawing ImGui Layer Frame");
  debug_layer_.DrawFrame();
};
void Renderer::SwapBuffers()
{
  LOG_DEBUG("Swapping buffers");
  window_manager_.SwapBuffers();
}
} // namespace Squirrel
