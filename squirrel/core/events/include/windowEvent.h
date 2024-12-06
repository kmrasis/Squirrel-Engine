#pragma once

#include "event.h"

namespace Squirrel
{
class WindowEvent : public Event
{
public:
  WindowEvent(const EventType& event_type, const float& height, const float& width);
  ~WindowEvent();

  float GetWindowHeight();
  void SetWindowHeight(const float& height);

  float GetWindowWidth();
  void SetWindowWidth(const float& width);

  std::string Log() const override;

protected:
  float height_;
  float width_;
};
} // namespace Squirrel
