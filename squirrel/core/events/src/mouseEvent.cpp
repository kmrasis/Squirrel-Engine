#include "mouseEvent.h"

#include <sstream>

namespace Squirrel
{

MouseEvent::MouseEvent(const EventType& event_type, const float& pos_x, const float& pos_y, const float& off_x,
                       const float& off_y, const int& button, const int& repeat_count)
    : Event(event_type),
      position_x_(pos_x),
      position_y_(pos_y),
      offset_x_(off_x),
      offset_y_(off_y),
      button_(button),
      repeat_count_(repeat_count)
{}
MouseEvent::~MouseEvent() = default;

float MouseEvent::GetPositionX() { return position_x_; }
void MouseEvent::SetPositionX(const float& pos_x) { position_x_ = pos_x; }

float MouseEvent::GetPositionY() { return position_y_; }
void MouseEvent::SetPositionY(const float& pos_y) { position_y_ = pos_y; }

float MouseEvent::GetOffsetX() { return offset_x_; }
void MouseEvent::SetOffsetX(const float& off_x) { offset_x_ = off_x; }

float MouseEvent::GetOffsetY() { return offset_y_; }
void MouseEvent::SetOffsetY(const float& off_y) { offset_y_ = off_y; }

float MouseEvent::GetButton() { return button_; }
void MouseEvent::SetButton(const float& button) { button_ = button; }

float MouseEvent::GetRepeatCount() { return repeat_count_; }
void MouseEvent::SetRepeatCount(const float& repeat_count) { repeat_count_ = repeat_count; }

std::string MouseEvent::Log() const
{
  std::stringstream ss;
  ss << "EventType : " << GetEventName();
  ss << ", isHandled : " << is_handled_;
  ss << ", positionX : " << position_x_;
  ss << ", positionY : " << position_y_;
  ss << ", offsetX : " << offset_x_;
  ss << ", offsetY : " << offset_y_;
  ss << ", Button : " << button_;
  ss << ", Repeat : " << repeat_count_;
  return ss.str();
}
} // namespace Squirrel
