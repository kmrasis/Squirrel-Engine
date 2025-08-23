#pragma once

#include "event.h"

namespace Squirrel
{
class MouseButtonEvent : public Event
{
public:
  MouseButtonEvent(const EventType& event_type, const int& button, const int& mods);
  ~MouseButtonEvent();

  int GetButton() const;
  int GetMods() const;
  const std::string Log() const override;

private:
  int button_;
  int mods_;
};

class MouseMoveEvent : public Event
{
public:
  MouseMoveEvent(const EventType& event_type, const double& pos_x, const double& pos_y);
  ~MouseMoveEvent();

  double GetPositionX() const;
  double GetPositionY() const;
  const std::string Log() const override;

private:
  double position_x_;
  double position_y_;
};

class MouseScrollEvent : public Event
{
public:
  MouseScrollEvent(const EventType& event_type, const double& off_x, const double& off_y);
  ~MouseScrollEvent();

  double GetOffsetX() const;
  double GetOffsetY() const;
  const std::string Log() const override;

private:
  double offset_x_;
  double offset_y_;
};
} // namespace Squirrel
