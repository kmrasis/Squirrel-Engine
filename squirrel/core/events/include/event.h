#pragma once

#include "eventTypes.h"

#include <string>

namespace Squirrel
{
class Event
{
public:
  Event(const EventType& event_type, const bool& is_handled = false);
  ~Event();

  const EventType GetEventType() const;
  bool IsHandled() const;
  void SetAsHandled(const bool& is_handled);
  const std::string GetEventName() const;
  virtual const std::string Log() const;

private:
  EventType event_type_;
  bool is_handled_;
};
} // namespace Squirrel
