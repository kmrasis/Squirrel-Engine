#include "mouseEvent.h"

#include <sstream>

namespace Squirrel
{

MouseEvent::MouseEvent(const EventType& event_type, const double& pos_x, const double& pos_y, const double& off_x,
                       const double& off_y, const int& button, const int& mods)
    : Event(event_type),
      position_x_(pos_x),
      position_y_(pos_y),
      offset_x_(off_x),
      offset_y_(off_y),
      button_(button),
      mods_(mods)
{}
MouseEvent::~MouseEvent() = default;

double MouseEvent::GetPositionX() { return position_x_; }
void MouseEvent::SetPositionX(const double& pos_x) { position_x_ = pos_x; }

double MouseEvent::GetPositionY() { return position_y_; }
void MouseEvent::SetPositionY(const double& pos_y) { position_y_ = pos_y; }

double MouseEvent::GetOffsetX() { return offset_x_; }
void MouseEvent::SetOffsetX(const double& off_x) { offset_x_ = off_x; }

double MouseEvent::GetOffsetY() { return offset_y_; }
void MouseEvent::SetOffsetY(const double& off_y) { offset_y_ = off_y; }

int MouseEvent::GetButton() { return button_; }
void MouseEvent::SetButton(const int& button) { button_ = button; }

int MouseEvent::GetMods() { return mods_; }
void MouseEvent::SetMods(const int& mods) { mods_ = mods; }

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
  ss << ", Mods : " << mods_;
  return ss.str();
}
} // namespace Squirrel
