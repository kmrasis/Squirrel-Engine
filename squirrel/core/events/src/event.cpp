#include "event.h"

#include <sstream>

namespace Squirrel
{

    /*
     * Events in Squirrel are currently blocking, meaning when an event occurs it
     * immediately gets dispatched and must be dealt with right then an there.
     * For the future, a better strategy might be to buffer events in an event
     * bus and process them during the "event" part of the update stag
     */

    Event::Event(const EventType &event_type, const bool &is_handled)
        : event_type_(event_type),
          is_handled_(is_handled) {}

    Event::~Event() = default;

    EventType Event::GetEventType() { return event_type_; }
    void Event::SetEventType(const EventType &event_type) { event_type_ = event_type; }

    std::string Event::GetEventName() const
    {
        switch (event_type_)
        {
        case EventType::WindowClose:
            return "WindowClose";
        case EventType::WindowResize:
            return "WindowResize";
        case EventType::WindowFocus:
            return "WindowFocus";
        case EventType::WindowUnfocus:
            return "WindowUnfocus";
        case EventType::WindowMove:
            return "WindowMove";
        case EventType::AppTick:
            return "AppTick";
        case EventType::AppUpdate:
            return "AppUpdate";
        case EventType::AppRender:
            return "AppRender";
        case EventType::KeyPress:
            return "KeyPress";
        case EventType::KeyRelease:
            return "KeyRelease";
        case EventType::MouseButtonPress:
            return "MouseButtonPress";
        case EventType::MouseButtonRelease:
            return "MouseButtonRelease";
        case EventType::MouseMove:
            return "MouseMove";
        case EventType::MouseScroll:
            return "MouseScroll";
        case EventType::Unknown:
            return "Unknown";
        }
        return "Unknown";
    }

    bool Event::IsHandled() { return is_handled_; }
    void Event::SetAsHandled(const bool &is_handled) { is_handled_ = is_handled; }

    std::string Event::Log() const
    {
        std::stringstream ss;
        ss << "EventType : " << GetEventName()
           << ", isHandled : " << is_handled_;
        return ss.str();
    }
} // namespace Squirrel
