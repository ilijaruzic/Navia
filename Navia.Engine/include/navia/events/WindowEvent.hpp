#ifndef _WINDOWEVENT_HPP_
#define _WINDOWEVENT_HPP_

#include "navia/events/Event.hpp"

namespace Navia {
class WindowResizeEvent : public Event {
public:
    WindowResizeEvent(uint32_t width, uint32_t height);

    uint32_t getWidth() const;
    uint32_t getHeight() const;

    std::string toString() const override;

    EVENT_CLASS_CATEGORY(EventCategory::WindowEvents)
    EVENT_CLASS_TYPE(EventType::WindowResize)

private:
    uint32_t width;
    uint32_t height;
};

class WindowCloseEvent : public Event {
public:
    EVENT_CLASS_CATEGORY(EventCategory::WindowEvents)
    EVENT_CLASS_TYPE(EventType::WindowClose)
};
}

#endif