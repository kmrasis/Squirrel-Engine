#include "keyEvent.h"

#include <sstream>

namespace Squirrel
{

KeyboardEvent::KeyboardEvent(const EventType& event_type, const int& key_code, const int& repeat_count)
    : Event(event_type),
      key_code_(key_code),
      repeat_count_(repeat_count)
{}
KeyboardEvent::~KeyboardEvent() = default;

int KeyboardEvent::GetKeyCode() { return key_code_; }
void KeyboardEvent::SetKeyCode(const int& key_code) { key_code_ = key_code; }

int KeyboardEvent::GetRepeatCount() { return repeat_count_; }
void KeyboardEvent::SetRepeatCount(const int& repeat_count) { repeat_count_ = repeat_count; }

std::string KeyboardEvent::Log() const
{
  std::stringstream ss;
  ss << "EventType : " << GetEventName();
  ss << ", isHandled : " << is_handled_;
  ss << ", keyCode : " << key_code_;
  ss << ", repeat : " << repeat_count_;
  return ss.str();
}
} // namespace Squirrel
