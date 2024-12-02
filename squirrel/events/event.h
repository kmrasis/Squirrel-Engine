#pragma once

#include <cstdint>
#include <sstream>

namespace Squirrel
{

    /*
     * Events in Squirrel are currently blocking, meaning when an event occurs it
     * immediately gets dispatched and must be dealt with right then an there.
     * For the future, a better strategy might be to buffer events in an event
     * bus and process them during the "event" part of the update stag
     */

    enum class EventType : uint64_t
    {
        /*
         * EventType is a bitmask with 64 bits
         * Event Classification
         *     Input:
         *          Key: KeyPress, KeyRelease
         *          Mouse: MouseButtonPress, MouseButtonRelease, MouseMove, MouseScroll
         * 
         *     Window: WindowClose, WindowResize, WindowFocus, WindowUnfocus, WindowMove
         *  
         *     Application: AppTick, AppUpdate, AppRender
         */

        WindowClose =           0x000000000001,
        WindowResize =          0x000000000002,
        WindowFocus =           0x000000000004,
        WindowUnfocus =         0x000000000008,
        WindowMove =            0x000000000010, // Window events end
        AppTick =               0x000000010000,
        AppUpdate =             0x000000020000,
        AppRender =             0x000000040000, // Application events end
        KeyPress =              0x000010000000,
        KeyRelease =            0x000020000000, // Keyboard events end
        MouseButtonPress =      0x010000000000,
        MouseButtonRelease =    0x020000000000,
        MouseMove =             0x040000000000,
        MouseScroll =           0x080000000000, // Mouse events end

        Unknown =               0x000000000000  // Unknown/unassisgned EventType
    };

    class Event
    {
    public:
        Event(const EventType &event_type = EventType::Unknown, const bool &is_handled = false)
            : event_type_(event_type),
              is_handled_(is_handled) {};

        ~Event() = default;

        EventType GetEventType() { return event_type_; }
        void SetEventType(const EventType &event_type) {event_type_ = event_type;}

        std::string GetEventName() const {
             switch(event_type_) {
                case EventType::WindowClose : return "WindowClose"; 
                case EventType::WindowResize : return "WindowResize"; 
                case EventType::WindowFocus : return "WindowFocus"; 
                case EventType::WindowUnfocus : return "WindowUnfocus"; 
                case EventType::WindowMove : return "WindowMove"; 
                case EventType::AppTick : return "AppTick"; 
                case EventType::AppUpdate : return "AppUpdate"; 
                case EventType::AppRender : return "AppRender"; 
                case EventType::KeyPress : return "KeyPress"; 
                case EventType::KeyRelease : return "KeyRelease"; 
                case EventType::MouseButtonPress : return "MouseButtonPress"; 
                case EventType::MouseButtonRelease : return "MouseButtonRelease"; 
                case EventType::MouseMove : return "MouseMove"; 
                case EventType::MouseScroll : return "MouseScroll"; 
                case EventType::Unknown : return "Unknown"; 
             }
             return "Unknown";
        }

        bool IsHandled() { return is_handled_; }
        void SetAsHandled(const bool & is_handled) {is_handled_ = is_handled;}

        virtual std::string Log() const {
            std::stringstream ss;
			ss << "EventType : " << GetEventName()
               << ", isHandled : " << is_handled_;
			return ss.str();
        }

    protected:
        EventType event_type_;
        bool is_handled_;
    };


} // namespace Squirrel
