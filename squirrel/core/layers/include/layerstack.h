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
  std::vector<Layer*>::iterator layerBegin() { return layers_.begin(); }
  std::vector<Layer*>::iterator layerEnd() { return layers_.end() + insert_pos_ + 1; }
  std::vector<Layer*>::iterator overlayBegin() { return layerEnd(); }
  std::vector<Layer*>::iterator overlayEnd() { return layers_.end(); }
  std::vector<Layer*>::iterator begin() { return layers_.begin(); }
  std::vector<Layer*>::iterator end() { return layers_.end(); }

private:
  std::vector<Layer*> layers_ = {};
  unsigned int insert_pos_    = 0;
};
} // namespace Squirrel
