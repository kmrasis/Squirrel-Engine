#include "windowEvent.h"

#include <sstream>

namespace Squirrel
{
// WindowCloseEvent Impl
WindowCloseEvent::WindowCloseEvent(const EventType& event_type)
    : Event(event_type)
{}
WindowCloseEvent::~WindowCloseEvent() = default;

// WindowFocusEvent Impl
WindowFocusEvent ::WindowFocusEvent(const EventType& event_type)
    : Event(event_type)
{}
WindowFocusEvent::~WindowFocusEvent() = default;

// WindowMoveEvent Impl
WindowMoveEvent::WindowMoveEvent(const EventType& event_type, const int& pos_x, const int& pos_y)
    : Event(event_type),
      position_x_(pos_x),
      position_y_(pos_y)
{}
WindowMoveEvent::~WindowMoveEvent() = default;

int WindowMoveEvent::GetWindowPosX() const { return position_x_; }
int WindowMoveEvent::GetWindowPosY() const { return position_y_; }
std::string WindowMoveEvent::Log() const
{
  std::stringstream ss;
  ss << "EventType : " << GetEventName();
  ss << ", isHandled : " << IsHandled();
  ss << ", window posX : " << position_x_;
  ss << ", window posY : " << position_y_;
  return ss.str();
}

// WindowResizeEvent Impl
WindowResizeEvent::WindowResizeEvent(const EventType& event_type, const int& width, const int& height)
    : Event(event_type),
      width_(width),
      height_(height)
{}
WindowResizeEvent::~WindowResizeEvent() = default;

int WindowResizeEvent::GetWindowHeight() { return height_; }
int WindowResizeEvent::GetWindowWidth() { return width_; }
std::string WindowResizeEvent::Log() const
{
  std::stringstream ss;
  ss << "EventType : " << GetEventName();
  ss << ", isHandled : " << IsHandled();
  ss << ", windowHeight : " << height_;
  ss << ", windowWidth : " << width_;
  return ss.str();
}
} // namespace Squirrel
