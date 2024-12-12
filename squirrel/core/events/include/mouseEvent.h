#pragma once

#include "event.h"

namespace Squirrel
{
class MouseEvent : public Event
{
public:
  MouseEvent(const EventType& event_type, const double& pos_x, const double& pos_y, const double& off_x,
             const double& off_y, const int& button, const int& mods);
  ~MouseEvent();

  double GetPositionX();
  void SetPositionX(const double& pos_x);

  double GetPositionY();
  void SetPositionY(const double& pos_y);

  double GetOffsetX();
  void SetOffsetX(const double& off_x);

  double GetOffsetY();
  void SetOffsetY(const double& off_y);

  int GetButton();
  void SetButton(const int& button);

  int GetMods();
  void SetMods(const int& mods);

  std::string Log() const override;

protected:
  double position_x_;
  double position_y_;
  double offset_x_;
  double offset_y_;

  int button_;
  int mods_;
};
} // namespace Squirrel
