#ifndef _WINDOWEVENT_HPP_
#define _WINDOWEVENT_HPP_

#include "navia/events/Event.hpp"

namespace Navia {
class WindowResizeEvent : public Event {
public:
    WindowResizeEvent(size_t width, size_t height);

    size_t getWidth() const;
    size_t getHeight() const;

    std::string toString() const override;

    EVENT_CLASS_CATEGORY(EventCategory::WindowEvents)
    EVENT_CLASS_TYPE(EventType::WindowResize)

private:
    size_t width;
    size_t height;
};

class WindowCloseEvent : public Event {
public:
    EVENT_CLASS_CATEGORY(EventCategory::WindowEvents)
    EVENT_CLASS_TYPE(EventType::WindowClose)
};
}

#endif