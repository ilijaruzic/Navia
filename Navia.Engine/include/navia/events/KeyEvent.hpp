#ifndef _KEY_EVENT_HPP_
#define _KEY_EVENT_HPP_

#include "Event.hpp"

namespace Navia {
class KeyEvent : public Event {
public:
    size_t getKeyCode() const;

    EVENT_CLASS_CATEGORY(EventCategory::KeyboardEvents | EventCategory::InputEvents)

protected:
    size_t keyCode;

    KeyEvent(size_t keyCode);
};

class KeyPressedEvent : public KeyEvent {
public:
    KeyPressedEvent(size_t keyCode, size_t repeatCount);

    size_t getRepeatCount() const;

    std::string toString() const override;

    EVENT_CLASS_TYPE(EventType::KeyPressed)

private:
    size_t repeatCount;
};

class KeyReleasedEvent : public KeyEvent {
public:
    KeyReleasedEvent(size_t keyCode);

    std::string toString() const override;

    EVENT_CLASS_TYPE(EventType::KeyReleased)
};

class KeyTypedEvent : public KeyEvent {
public:
    KeyTypedEvent(size_t keyCode);

    std::string toString() const override;

    EVENT_CLASS_TYPE(EventType::KeyTyped)
};
}

#endif