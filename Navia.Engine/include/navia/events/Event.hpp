#ifndef _EVENT_HPP_
#define _EVENT_HPP_

#include "Core.hpp"

namespace Navia {
enum class EventType {
    None = 0,
    WindowResize, WindowMoved, WindowClose, WindowFocus, WindowLostFocus,
    ApplicationTick, ApplicationUpdate, ApplicationRender,
    KeyPressed, KeyReleased, KeyTyped,
    MouseMoved, MouseScrolled, MouseButtonPressed, MouseButtonReleased
};

enum class EventCategory {
    None                = 0,
    WindowEvents        = BIT(0),
    ApplicationEvents   = BIT(1),
    InputEvents         = BIT(2),
    KeyboardEvents      = BIT(3),
    MouseEvents         = BIT(4),
    MouseButtonEvents   = BIT(5)
};
int operator&(const EventCategory& lhs, const EventCategory& rhs);
int operator|(const EventCategory& lhs, const EventCategory& rhs);

#define EVENT_CLASS_TYPE(type) static EventType getStaticEventType() { return type; }\
                               EventType getEventType() const override { return getStaticEventType(); }\
                               std::string getEventName() const override { return #type; }

#define EVENT_CLASS_CATEGORY(category) int getCategoryFlags() const override { return static_cast<int>(category); }

class Event {
public:
    bool handled{false};

    virtual EventType getEventType() const = 0;
    virtual int getCategoryFlags() const = 0;
    bool isCategory(EventCategory category);

    virtual std::string getEventName() const = 0;
    virtual std::string toString() const { return getEventName().substr(11, getEventName().size()) + "Event"; }
    friend std::ostream& operator<<(std::ostream& ostream, const Event& rhs);
};

class EventDispatcher {
public:
    EventDispatcher(Event& event) : event(event) {}

    template<typename EventType, typename EventCallbackType>
    bool dispatch(const EventCallbackType& callback) {
        if (event.getEventType() == EventType::getStaticEventType()) {
            event.handled = callback(static_cast<EventType&>(event));
            return true;
        }
        return false;
    }

private:
    Event& event;
};
}

#endif