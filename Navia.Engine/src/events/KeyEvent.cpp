#include "navia/events/KeyEvent.hpp"

namespace Navia {
KeyEvent::KeyEvent(uint32_t keyCode) : keyCode(keyCode) {}

uint32_t KeyEvent::getKeyCode() const {
    return keyCode;
}

KeyPressedEvent::KeyPressedEvent(uint32_t keyCode, uint32_t repeatCount) : KeyEvent(keyCode), repeatCount(repeatCount) {}

uint32_t KeyPressedEvent::getRepeatCount() const {
    return repeatCount;
}

std::string KeyPressedEvent::toString() const {
    std::stringstream stream;
    stream << "KeyPressedEvent: " << keyCode << " (" << repeatCount << " repeats)";
    return stream.str();
}

KeyReleasedEvent::KeyReleasedEvent(uint32_t keyCode) : KeyEvent(keyCode) {}

std::string KeyReleasedEvent::toString() const {
    std::stringstream stream;
    stream << "KeyReleasedEvent: " << keyCode;
    return stream.str();
}

KeyTypedEvent::KeyTypedEvent(uint32_t keyCode) : KeyEvent(keyCode) {}

std::string KeyTypedEvent::toString() const {
    std::stringstream stream;
    stream << "KeyTypedEvent: " << keyCode;
    return stream.str();
}
}