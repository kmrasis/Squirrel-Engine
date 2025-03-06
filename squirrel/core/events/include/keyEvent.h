#pragma once

#include "event.h"

namespace Squirrel
{
class KeyboardEvent : public Event
{
public:
  KeyboardEvent(const EventType& event_type, const int& key, const int& scan_code, const int& mods);
  ~KeyboardEvent();

  int GetKey();
  void SetKey(const int& key);

  int GetScanCode();
  void SetScanCode(const int& scan_code);

  int GetMods();
  void SetMods(const int& mods);

  inline std::string Log() const override;

protected:
  int key_;
  int scan_code_;
  int mods_;
};
} // namespace Squirrel
