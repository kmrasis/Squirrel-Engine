#pragma once

#include "event.h"

namespace Squirrel
{
class ApplicationEvent : public Event
{
public:
  ApplicationEvent(const EventType& event_type);
  ~ApplicationEvent();
};
} // namespace Squirrel
