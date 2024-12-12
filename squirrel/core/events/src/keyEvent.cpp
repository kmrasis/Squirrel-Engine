#include "keyEvent.h"

#include <sstream>

namespace Squirrel
{

KeyboardEvent::KeyboardEvent(const EventType& event_type, const int& key, const int& scan_code, const int& mods)
    : Event(event_type),
      key_(key),
      scan_code_(scan_code),
      mods_(mods)
{}
KeyboardEvent::~KeyboardEvent() = default;

int KeyboardEvent::GetKey() { return key_; }
void KeyboardEvent::SetKey(const int& key) { key_ = key; }

int KeyboardEvent::GetScanCode() { return scan_code_; }
void KeyboardEvent::SetScanCode(const int& scan_code) { scan_code_ = scan_code; }

int KeyboardEvent::GetMods() { return mods_; }
void KeyboardEvent::SetMods(const int& mods) { mods_ = mods; }

std::string KeyboardEvent::Log() const
{
  std::stringstream ss;
  ss << "EventType : " << GetEventName();
  ss << ", isHandled : " << is_handled_;
  ss << ", key : " << key_;
  ss << ", scan code : " << scan_code_;
  ss << ", mods : " << mods_;
  return ss.str();
}
} // namespace Squirrel
