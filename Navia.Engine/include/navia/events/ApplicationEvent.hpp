#ifndef _APPLICATION_EVENT_HPP_
#define _APPLICATION_EVENT_HPP_

#include "Event.hpp"

namespace Navia {
class ApplicationTickEvent : public Event {
public:
    EVENT_CLASS_CATEGORY(EventCategory::ApplicationEvents);
    EVENT_CLASS_TYPE(EventType::ApplicationTick)
};

class ApplicationUpdateEvent : public Event {
public:
    EVENT_CLASS_CATEGORY(EventCategory::ApplicationEvents);
    EVENT_CLASS_TYPE(EventType::ApplicationUpdate)
};

class ApplicationRenderEvent : public Event {
public:
    EVENT_CLASS_CATEGORY(EventCategory::ApplicationEvents);
    EVENT_CLASS_TYPE(EventType::ApplicationRender)
};
}

#endif