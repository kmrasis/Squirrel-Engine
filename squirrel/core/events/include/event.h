#pragma once

#include "eventTypes.h"

#include <string>

namespace Squirrel
{

    /*
     * Events in Squirrel are currently blocking, meaning when an event occurs it
     * immediately gets dispatched and must be dealt with right then an there.
     * For the future, a better strategy might be to buffer events in an event
     * bus and process them during the "event" part of the update stag
     */

    class Event
    {
    public:
        Event(const EventType &event_type, const bool &is_handled = false);
        ~Event();

        EventType GetEventType();
        void SetEventType(const EventType &event_type);

        bool IsHandled();
        void SetAsHandled(const bool &is_handled);

        std::string GetEventName() const;
        virtual std::string Log() const;

    protected:
        EventType event_type_;
        bool is_handled_;
    };
} // namespace Squirrel
