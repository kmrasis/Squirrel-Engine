#include "layerstack.h"
#include "layer.h"
#include "log-impl.h"

#include <algorithm>

namespace Squirrel
{
LayerStack::LayerStack()  = default;
LayerStack::~LayerStack() = default;

void LayerStack::Init() { CONSOLE_INFO("Initialised Layerstack successfully"); }
void LayerStack::DeInit()
{
  auto it = layers_.begin();
  while (it != layers_.end())
  {
    Layer* layer = layers_.front();
    layer->Detach();
    delete layer;
    layer = nullptr;
    it    = layers_.erase(it);
  }
  insert_pos_ = 0;
  CONSOLE_INFO("DeInitialised Layerstack successfully");
}

void LayerStack::PushLayer(Layer* layer)
{
  layers_.insert(layerEnd() - 1, layer);
  layers_[insert_pos_]->Attach();
  ++insert_pos_;
  CONSOLE_INFO("Pushed layer [{}] to stack. Stack Size [{}]", layer->GetName(), layers_.size());
}
void LayerStack::PushOverlay(Layer* overlay)
{
  layers_.push_back(overlay);
  layers_.back()->Attach();
  CONSOLE_INFO("Pushed overlay [{}] to stack. Stack size [{}]", overlay->GetName(), layers_.size());
}

void LayerStack::PopLayer(Layer* layer)
{
  auto it = std::find(layerBegin(), layerEnd(), layer);
  if (it != layerEnd())
  {
    layer->Detach();
    layers_.erase(it);
    --insert_pos_;
    CONSOLE_INFO("Popped layer [{}]. Stack size [{}]", layer->GetName(), layers_.size());
  } else
  {
    CONSOLE_ERROR("No layer [{}] found in layerstack", layer->GetName());
  }
  delete layer; // Delete layer to ensure memory is released in both cases
  layer = nullptr;
}
void LayerStack::PopOverlay(Layer* overlay)
{
  auto it = std::find(overlayBegin(), overlayEnd(), overlay);
  if (it != overlayEnd())
  {
    overlay->Detach();
    layers_.erase(it);
    CONSOLE_INFO("Popped overlay [{}]. Stack size [{}]", overlay->GetName(), layers_.size());
  } else
  {
    CONSOLE_ERROR("No overlay [{}] found in layerstack", overlay->GetName());
  }
  delete overlay; // Delete overlayer to ensure memory is released in both cases
  overlay = nullptr;
}

void LayerStack::Update()
{
  LOG_DEBUG("Updating layerstack");
  for (auto& layer : layers_)
  {
    layer->Update();
  }
}
} // namespace Squirrel
