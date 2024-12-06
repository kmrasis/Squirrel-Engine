#pragma once

#include "event.h"

namespace Squirrel
{
class MouseEvent : public Event
{
public:
  MouseEvent(const EventType& event_type, const float& pos_x, const float& pos_y, const float& off_x,
             const float& off_y, const int& button, const int& repeat_count = 0);
  ~MouseEvent();

  float GetPositionX();
  void SetPositionX(const float& pos_x);

  float GetPositionY();
  void SetPositionY(const float& pos_y);

  float GetOffsetX();
  void SetOffsetX(const float& off_x);

  float GetOffsetY();
  void SetOffsetY(const float& off_y);

  float GetButton();
  void SetButton(const float& button);

  float GetRepeatCount();
  void SetRepeatCount(const float& repeat_count);

  std::string Log() const override;

protected:
  float position_x_;
  float position_y_;
  float offset_x_;
  float offset_y_;

  int button_;
  int repeat_count_;
};
} // namespace Squirrel
