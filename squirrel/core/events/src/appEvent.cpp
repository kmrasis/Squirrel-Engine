#include "appEvent.h"

namespace Squirrel
{

ApplicationEvent::ApplicationEvent(const EventType& event_type)
    : Event(event_type)
{}

ApplicationEvent::~ApplicationEvent() = default;
} // namespace Squirrel
