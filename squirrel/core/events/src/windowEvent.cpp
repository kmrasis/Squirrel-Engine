#include "windowEvent.h"

#include <sstream>

namespace Squirrel
{

    WindowEvent::WindowEvent(const EventType &event_type, const float &height, const float &width)
        : Event(event_type),
          height_(height),
          width_(width) {}
    WindowEvent::~WindowEvent() = default;

    float WindowEvent::GetWindowHeight() { return height_; }
    void WindowEvent::SetWindowHeight(const float &height) { height_ = height; }

    float WindowEvent::GetWindowWidth() { return width_; }
    void WindowEvent::SetWindowWidth(const float &width) { width_ = width; }

    std::string WindowEvent::Log() const
    {
        std::stringstream ss;
        ss << "EventType : " << GetEventName()
           << ", isHandled : " << is_handled_
           << ", windowHeight : " << height_
           << ", windowWidth : " << width_;
        return ss.str();
    }
} // namespace Squirrel
