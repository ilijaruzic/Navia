#include "navia/events/KeyEvent.hpp"

namespace Navia {
KeyEvent::KeyEvent(size_t keyCode) : keyCode(keyCode) {}

size_t KeyEvent::getKeyCode() const {
    return keyCode;
}

KeyPressedEvent::KeyPressedEvent(size_t keyCode, size_t repeatCount) : KeyEvent(keyCode), repeatCount(repeatCount) {}

size_t KeyPressedEvent::getRepeatCount() const {
    return repeatCount;
}

std::string KeyPressedEvent::toString() const {
    std::stringstream stream;
    stream << "KeyPressedEvent: " << keyCode << " (" << repeatCount << " repeats)";
    return stream.str();
}

KeyReleasedEvent::KeyReleasedEvent(size_t keyCode) : KeyEvent(keyCode) {}

std::string KeyReleasedEvent::toString() const {
    std::stringstream stream;
    stream << "KeyReleasedEvent: " << keyCode;
    return stream.str();
}

KeyTypedEvent::KeyTypedEvent(size_t keyCode) : KeyEvent(keyCode) {}

std::string KeyTypedEvent::toString() const {
    std::stringstream stream;
    stream << "KeyTypedEvent: " << keyCode;
    return stream.str();
}
}