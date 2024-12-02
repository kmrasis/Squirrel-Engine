#pragma once

#include "event.h"

namespace Squirrel
{
    class MouseEvent : public Event
    {
    public:
        MouseEvent(const EventType &event_type, const float &pos_x, const float &pos_y,
                   const float &off_x, const float &off_y, const int &button,
                   const int &repeat_count = 0)
            : Event(event_type),
              position_x_(pos_x),
              position_y_(pos_y),
              offset_x_(off_x),
              offset_y_(off_y),
              button_(button),
              repeat_count_(repeat_count) {}

        ~MouseEvent() = default;

        float GetPositionX() { return position_x_; }
        void SetPositionX(const float &pos_x) { position_x_ = pos_x; }

        float GetPositionY() { return position_y_; }
        void SetPositionY(const float &pos_y) { position_y_ = pos_y; }

        float GetOffsetX() { return offset_x_; }
        void SetOffsetX(const float &off_x) { offset_x_ = off_x; }

        float GetOffsetY() { return offset_y_; }
        void SetOffsetY(const float &off_y) { offset_y_ = off_y; }

        float GetButton() { return button_; }
        void SetButton(const float &button) { button_ = button; }

        float GetRepeatCount() { return repeat_count_; }
        void SetRepeatCount(const float &repeat_count) { repeat_count_ = repeat_count; }

        std::string Log() const override {
            std::stringstream ss;
			ss << "EventType : " << GetEventName()
               << ", isHandled : " << is_handled_
               << ", positionX : " << position_x_
               << ", positionY : " << position_y_
               << ", offsetX : " << offset_x_
               << ", offsetY : " << offset_y_
               << ", Button : " << button_
               << ", Repeat : " << repeat_count_;
			return ss.str();
        }

    protected:
        float position_x_;
        float position_y_;
        float offset_x_;
        float offset_y_;

        int button_;
        int repeat_count_;
    };
} // namespace Squirrel
