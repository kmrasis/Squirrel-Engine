#pragma once

#include <vector>

namespace Squirrel
{
class Layer;
class LayerStack
{
public:
  LayerStack();
  ~LayerStack();
  void Init();
  void DeInit();
  void PushLayer(Layer* layer);
  void PushOverlay(Layer* overlay);
  void PopLayer(Layer* layer);
  void PopOverlay(Layer* overlay);
  void Update();
  std::vector<Layer*>::iterator begin() { return layers_.begin(); }
  std::vector<Layer*>::iterator end() { return layers_.end(); }

private:
  std::vector<Layer*> layers_;
  std::vector<Layer*>::iterator layer_insert_;
};
} // namespace Squirrel
