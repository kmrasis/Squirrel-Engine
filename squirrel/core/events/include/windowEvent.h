#pragma once

#include "event.h"

namespace Squirrel
{
class WindowEvent : public Event
{
public:
  WindowEvent(const EventType& event_type, const int& pos_x, const int& pos_y, const int& width, const int& height);
  ~WindowEvent();

  int GetWindowHeight();
  void SetWindowHeight(const int& height);

  int GetWindowWidth();
  void SetWindowWidth(const int& width);

  int GetWindowPosX();
  void SetWindowPosX(const int& pos_x);

  int GetWindowPosY();
  void SetWindowPosY(const int& pos_y);

  inline std::string Log() const override;

protected:
  int height_;
  int width_;
  int position_x_;
  int position_y_;
};
} // namespace Squirrel
