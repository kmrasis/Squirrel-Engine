#include "windowEvent.h"

#include <sstream>

namespace Squirrel
{

WindowEvent::WindowEvent(const EventType& event_type, const int& pos_x, const int& pos_y, const int& width,
                         const int& height)
    : Event(event_type),
      position_x_(pos_x),
      position_y_(pos_y),
      width_(width),
      height_(height)
{}
WindowEvent::~WindowEvent() = default;

int WindowEvent::GetWindowHeight() { return height_; }
void WindowEvent::SetWindowHeight(const int& height) { height_ = height; }

int WindowEvent::GetWindowWidth() { return width_; }
void WindowEvent::SetWindowWidth(const int& width) { width_ = width; }

int WindowEvent::GetWindowPosX() { return position_x_; }
void WindowEvent::SetWindowPosX(const int& pos_x) { position_x_ = pos_x; };

int WindowEvent::GetWindowPosY() { return position_y_; };
void WindowEvent::SetWindowPosY(const int& pos_y) { position_y_ = pos_y; };

std::string WindowEvent::Log() const
{
  std::stringstream ss;
  ss << "EventType : " << GetEventName();
  ss << ", isHandled : " << is_handled_;
  ss << ", window posX : " << position_x_;
  ss << ", window posY : " << position_y_;
  ss << ", windowHeight : " << height_;
  ss << ", windowWidth : " << width_;
  return ss.str();
}
} // namespace Squirrel
