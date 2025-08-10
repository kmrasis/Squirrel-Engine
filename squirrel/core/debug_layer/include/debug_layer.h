#pragma once
#include "layer.h"

namespace Squirrel
{
class DebugLayer : public Layer
{
public:
  DebugLayer();
  ~DebugLayer();

  void Attach() override;
  void Detach() override;
  void Update() override;
  void HandleEvent(const std::shared_ptr<Event> event) override;
};
} // namespace Squirrel
