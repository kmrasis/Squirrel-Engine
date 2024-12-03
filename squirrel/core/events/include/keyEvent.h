#pragma once

#include "event.h"

namespace Squirrel
{
    class KeyboardEvent : public Event
    {
    public:
        KeyboardEvent(const EventType &event_type, const int &key_code, const int &repeat_count = 0);
        ~KeyboardEvent();

        int GetKeyCode();
        void SetKeyCode(const int &key_code);

        int GetRepeatCount();
        void SetRepeatCount(const int &repeat_count);

        std::string Log() const override;

    protected:
        int key_code_;
        int repeat_count_;
    };
} // namespace Squirrel
