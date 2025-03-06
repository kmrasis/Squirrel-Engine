#include "layerstack.h"
#include "layer.h"
#include "log-impl.h"

#include <algorithm>

namespace Squirrel
{
LayerStack::LayerStack()  = default;
LayerStack::~LayerStack() = default;

void LayerStack::Init()
{
  layer_insert_ = layers_.begin();
  CONSOLE_INFO("Initialised Layerstack successfully");
}
void LayerStack::DeInit()
{
  for (Layer* layer : layers_)
    delete layer;
}

void LayerStack::PushLayer(Layer* layer) { layer_insert_ = layers_.emplace(layer_insert_, layer); }
void LayerStack::PushOverlay(Layer* overlay) { layers_.emplace_back(overlay); }

void LayerStack::PopLayer(Layer* layer)
{
  auto it = std::find(layers_.begin(), layers_.end(), layer);
  if (it != layers_.end())
  {
    layers_.erase(it);
    layer_insert_--;
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
