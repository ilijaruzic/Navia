#ifndef _KEY_EVENT_HPP_
#define _KEY_EVENT_HPP_

#include "navia/events/Event.hpp"

namespace Navia {
class KeyEvent : public Event {
public:
    uint32_t getKeyCode() const;

    EVENT_CLASS_CATEGORY(EventCategory::KeyboardEvents | EventCategory::InputEvents)

protected:
    uint32_t keyCode;

    KeyEvent(uint32_t keyCode);
};

class KeyPressedEvent : public KeyEvent {
public:
    KeyPressedEvent(uint32_t keyCode, uint32_t repeatCount);

    uint32_t getRepeatCount() const;

    std::string toString() const override;

    EVENT_CLASS_TYPE(EventType::KeyPressed)

private:
    uint32_t repeatCount;
};

class KeyReleasedEvent : public KeyEvent {
public:
    KeyReleasedEvent(uint32_t keyCode);

    std::string toString() const override;

    EVENT_CLASS_TYPE(EventType::KeyReleased)
};

class KeyTypedEvent : public KeyEvent {
public:
    KeyTypedEvent(uint32_t keyCode);

    std::string toString() const override;

    EVENT_CLASS_TYPE(EventType::KeyTyped)
};
}

#endif