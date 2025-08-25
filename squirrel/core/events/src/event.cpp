#include "event.h"

#include <sstream>

namespace Squirrel
{
Event::Event(const EventType& event_type, const bool& is_handled)
    : event_type_(event_type),
      is_handled_(is_handled)
{}
Event::~Event() = default;
EventType Event::GetEventType() const { return event_type_; }
std::string Event::GetEventName() const
{
  switch (event_type_)
  {
    case EventType::WindowClose:
      return "WindowClose";
    case EventType::WindowResize:
      return "WindowResize";
    case EventType::WindowFocus:
      return "WindowFocus";
    case EventType::WindowUnfocus:
      return "WindowUnfocus";
    case EventType::WindowMove:
      return "WindowMove";
    case EventType::AppTick:
      return "AppTick";
    case EventType::AppUpdate:
      return "AppUpdate";
    case EventType::AppRender:
      return "AppRender";
    case EventType::KeyPress:
      return "KeyPress";
    case EventType::KeyRelease:
      return "KeyRelease";
    case EventType::KeyRepeat:
      return "KeyRepeat";
    case EventType::KeyType:
      return "KeyType";
    case EventType::MouseButtonPress:
      return "MouseButtonPress";
    case EventType::MouseButtonRelease:
      return "MouseButtonRelease";
    case EventType::MouseMove:
      return "MouseMove";
    case EventType::MouseScroll:
      return "MouseScroll";
    case EventType::Unknown:
      return "Unknown";
  }
  return "NotHandled";
}

bool Event::IsHandled() const { return is_handled_; }
void Event::SetAsHandled(const bool& is_handled) { is_handled_ = is_handled; }
std::string Event::Log() const
{
  std::stringstream ss;
  ss << "EventType : " << GetEventName();
  ss << ", isHandled : " << is_handled_;
  return ss.str();
}
} // namespace Squirrel
