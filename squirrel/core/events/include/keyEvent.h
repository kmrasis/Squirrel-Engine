#pragma once

#include "event.h"

namespace Squirrel
{
class KeyPressEvent : public Event
{
public:
  KeyPressEvent(const EventType& event_type, const int& key, const int& scan_code, const int& mods);
  ~KeyPressEvent();

  int GetKey() const;
  int GetScanCode() const;
  int GetMods() const;
  std::string Log() const override;

private:
  int key_;
  int scan_code_;
  int mods_;
};

class KeyTypeEvent : public Event
{
public:
  KeyTypeEvent(const EventType& event_type, const unsigned int& codepoint);
  ~KeyTypeEvent();

  unsigned int GetCodePoint() const;
  std::string Log() const override;

private:
  unsigned int codepoint_;
};
} // namespace Squirrel
