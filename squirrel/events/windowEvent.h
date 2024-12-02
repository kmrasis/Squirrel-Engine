#pragma once

#include "event.h"

namespace Squirrel
{
    class WindowEvent : public Event
    {
    public:
        WindowEvent(const EventType &event_type, const float &height, const float &width)
        : Event(event_type),
          height_(height),
          width_(width) {}

        ~WindowEvent() = default;

        float GetWindowHeight() {return height_;}
        void SetWindowHeight(const float &height) {height_ = height;}

        float GetWindowWidth() {return width_;}
        void SetWindowWidth(const float &width) {width_ = width;}

        std::string Log() const override {
            std::stringstream ss;
			ss << "EventType : " << GetEventName()
               << ", isHandled : " << is_handled_
               << ", windowHeight : " << height_
               << ", windowWidth : " << width_;
			return ss.str();
        }

    protected:
        float height_;
        float width_;
    };
} // namespace Squirrel
