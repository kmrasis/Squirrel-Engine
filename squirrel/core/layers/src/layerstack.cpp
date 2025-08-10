#include "layerstack.h"
#include "layer.h"
#include "log-impl.h"

#include <algorithm>

namespace Squirrel
{
LayerStack::LayerStack()  = default;
LayerStack::~LayerStack() = default;

void LayerStack::Init() { CONSOLE_INFO("Initialised Layerstack successfully"); }
void LayerStack::DeInit() {}

void LayerStack::PushLayer(Layer* layer)
{
  layers_.emplace(layers_.begin() + layers_inserted_, layer);
  ++layers_inserted_;
  layer->Attach();
}
void LayerStack::PushOverlay(Layer* overlay)
{
  layers_.emplace_back(overlay);
  overlay->Attach();
}

void LayerStack::PopLayer(Layer* layer)
{
  auto first = layers_.begin();
  auto last  = layers_.end() - layers_inserted_;
  auto it    = std::find(first, last, layer);
  if (it != last)
  {
    Layer* layer = *it;
    layer->Detach();

    delete layer;
    layer = nullptr;
    layers_.erase(it);
    --layers_inserted_;
  }
}
void LayerStack::PopOverlay(Layer* overlay)
{
  auto it = std::find(layers_.begin(), layers_.end(), overlay);
  if (it != layers_.end())
    layers_.erase(it);
}

void LayerStack::Update()
{
  for (auto& layer : layers_)
  {
    layer->Update();
  }
}
} // namespace Squirrel
