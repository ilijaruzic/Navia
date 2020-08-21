#ifndef _MOUSE_EVENT_HPP_
#define _MOUSE_EVENT_HPP_

#include "navia/events/Event.hpp"

namespace Navia {
class MouseMovedEvent : public Event {
public:
    MouseMovedEvent(float x, float y);

    float getX() const;
    float getY() const;

    std::string toString() const override;

    EVENT_CLASS_CATEGORY(EventCategory::MouseEvents | EventCategory::InputEvents)
    EVENT_CLASS_TYPE(EventType::MouseMoved)

private:
    float x;
    float y;
};

class MouseScrolledEvent : public Event {
public:
    MouseScrolledEvent(float xOffset, float yOffset);

    float getXOffset() const;
    float getYOffset() const;

    std::string toString() const override;

    EVENT_CLASS_CATEGORY(EventCategory::MouseEvents | EventCategory::InputEvents)
    EVENT_CLASS_TYPE(EventType::MouseScrolled)

private:
    float xOffset;
    float yOffset;
};

class MouseButtonEvent : public Event {
public:
    size_t getMouseButton() const;

    EVENT_CLASS_CATEGORY(EventCategory::MouseEvents | EventCategory::InputEvents)

protected:
    size_t mouseButton;

    MouseButtonEvent(size_t mouseButton);
};

class MouseButtonPressedEvent : public MouseButtonEvent {
public:
    MouseButtonPressedEvent(size_t mouseButton);

    std::string toString() const override;

    EVENT_CLASS_TYPE(EventType::MouseButtonPressed)
};

class MouseButtonReleasedEvent : public MouseButtonEvent {
public:
    MouseButtonReleasedEvent(size_t mouseButton);

    std::string toString() const override;

    EVENT_CLASS_TYPE(EventType::MouseButtonReleased)
};
}

#endif