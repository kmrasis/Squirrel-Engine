#pragma once

#include "event.h"

namespace Squirrel
{
    class KeyboardEvent : public Event
    {
    public:
        KeyboardEvent(const EventType &event_type, const int &key_code, const int &repeat_count = 0)
            : Event(event_type),
              key_code_(key_code),
              repeat_count_(repeat_count) {}

        ~KeyboardEvent() = default;

        int GetKeyCode() { return key_code_; }
        void SetKeyCode(const int &key_code) { key_code_ = key_code; }

        int GetRepeatCount() { return repeat_count_; }
        void SetRepeatCount(const int &repeat_count) { repeat_count_ = repeat_count; }

        std::string Log() const override {
            std::stringstream ss;
			ss << "EventType : " << GetEventName()
               << ", isHandled : " << is_handled_
               << ", keyCode : " << key_code_
               << ", repeat : " << repeat_count_;
			return ss.str();
        }

    protected:
        int key_code_;
        int repeat_count_;
    };
} // namespace Squirrel
