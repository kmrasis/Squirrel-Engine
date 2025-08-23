#pragma once

#include "event.h"

namespace Squirrel
{
class WindowCloseEvent : public Event
{
public:
  WindowCloseEvent(const EventType& event_type);
  ~WindowCloseEvent();
};

class WindowFocusEvent : public Event
{
public:
  WindowFocusEvent(const EventType& event_type);
  ~WindowFocusEvent();
};

class WindowMoveEvent : public Event
{
public:
  WindowMoveEvent(const EventType& event_type, const int& pos_x, const int& pos_y);
  ~WindowMoveEvent();

  int GetWindowPosX() const;
  int GetWindowPosY() const;
  const std::string Log() const override;

private:
  int position_x_;
  int position_y_;
};

class WindowResizeEvent : public Event
{
public:
  WindowResizeEvent(const EventType& event_type, const int& width, const int& height);
  ~WindowResizeEvent();

  int GetWindowHeight();
  int GetWindowWidth();
  const std::string Log() const override;

private:
  int height_;
  int width_;
};
} // namespace Squirrel
