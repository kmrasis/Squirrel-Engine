#include "mouseEvent.h"

#include <sstream>

namespace Squirrel
{
// MouseButtonEvent Impl
MouseButtonEvent::MouseButtonEvent(const EventType& event_type, const int& button, const int& mods)
    : Event(event_type),
      button_(button),
      mods_(mods)
{}
MouseButtonEvent::~MouseButtonEvent() = default;

int MouseButtonEvent::GetButton() const { return button_; }
int MouseButtonEvent::GetMods() const { return mods_; }
std::string MouseButtonEvent::Log() const
{
  std::stringstream ss;
  ss << "EventType : " << GetEventName();
  ss << ", isHandled : " << IsHandled();
  ss << ", Button : " << GetButton();
  ss << ", Mods : " << GetMods();
  return ss.str();
}

// MouseMoveEvent Impl
MouseMoveEvent::MouseMoveEvent(const EventType& event_type, const double& pos_x, const double& pos_y)
    : Event(event_type),
      position_x_(pos_x),
      position_y_(pos_y)
{}
MouseMoveEvent::~MouseMoveEvent() = default;

double MouseMoveEvent::GetPositionX() const { return position_x_; }
double MouseMoveEvent::GetPositionY() const { return position_y_; }
std::string MouseMoveEvent::Log() const
{
  std::stringstream ss;
  ss << "EventType : " << GetEventName();
  ss << ", isHandled : " << IsHandled();
  ss << ", Position X : " << GetPositionX();
  ss << ", Position Y : " << GetPositionY();
  return ss.str();
}

// MouseScrollEvent Impl
MouseScrollEvent::MouseScrollEvent(const EventType& event_type, const double& off_x, const double& off_y)
    : Event(event_type),
      offset_x_(off_x),
      offset_y_(off_y)
{}
MouseScrollEvent::~MouseScrollEvent() = default;

double MouseScrollEvent::GetOffsetX() const { return offset_x_; }
double MouseScrollEvent::GetOffsetY() const { return offset_y_; }
std::string MouseScrollEvent::Log() const
{
  std::stringstream ss;
  ss << "EventType : " << GetEventName();
  ss << ", isHandled : " << IsHandled();
  ss << ", offsetX : " << GetOffsetX();
  ss << ", offsetY : " << GetOffsetY();
  return ss.str();
}
} // namespace Squirrel
