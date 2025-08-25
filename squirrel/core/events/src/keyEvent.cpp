#include "keyEvent.h"

#include <sstream>

namespace Squirrel
{
// KeyPressEvent Impl
KeyPressEvent::KeyPressEvent(const EventType& event_type, const int& key, const int& scan_code, const int& mods)
    : Event(event_type),
      key_(key),
      scan_code_(scan_code),
      mods_(mods)
{}
KeyPressEvent::~KeyPressEvent() = default;

int KeyPressEvent::GetKey() const { return key_; }
int KeyPressEvent::GetScanCode() const { return scan_code_; }
int KeyPressEvent::GetMods() const { return mods_; }
std::string KeyPressEvent::Log() const
{
  std::stringstream ss;
  ss << "EventType : " << GetEventName();
  ss << ", isHandled : " << IsHandled();
  ss << ", key : " << key_;
  ss << ", scan code : " << scan_code_;
  ss << ", mods : " << mods_;
  return ss.str();
}

// KeyTypeEvent Impl
KeyTypeEvent::KeyTypeEvent(const EventType& event_type, const unsigned int& codepoint)
    : Event(event_type),
      codepoint_(codepoint)
{}
KeyTypeEvent::~KeyTypeEvent() = default;

unsigned int KeyTypeEvent::GetCodePoint() const { return codepoint_; }
std::string KeyTypeEvent::Log() const
{
  std::stringstream ss;
  ss << "EventType : " << GetEventName();
  ss << ", isHandled : " << IsHandled();
  ss << ", codepoint : " << GetCodePoint();
  return ss.str();
}
} // namespace Squirrel
