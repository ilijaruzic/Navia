#include "MouseEvent.hpp"

namespace Navia {
MouseMovedEvent::MouseMovedEvent(float x, float y) : x(x), y(y) {}

float MouseMovedEvent::getX() const {
    return x;
}

float MouseMovedEvent::getY() const {
    return y;
}

std::string MouseMovedEvent::toString() const {
    std::stringstream stream;
    stream << "MouseMovedEvent: " << x << ", " << y;
    return stream.str();
}

MouseScrolledEvent::MouseScrolledEvent(float xOffset, float yOffset) : xOffset(xOffset), yOffset(yOffset) {}

float MouseScrolledEvent::getXOffset() const {
    return xOffset;
}

float MouseScrolledEvent::getYOffset() const {
    return yOffset;
}

std::string MouseScrolledEvent::toString() const {
    std::stringstream stream;
    stream << "MouseScrolledEvent: " << xOffset << ", " << yOffset;
    return stream.str();
}

MouseButtonEvent::MouseButtonEvent(size_t mouseButton) : mouseButton(mouseButton) {}

size_t MouseButtonEvent::getMouseButton() const {
    return mouseButton;
}

MouseButtonPressedEvent::MouseButtonPressedEvent(size_t mouseButton) : MouseButtonEvent(mouseButton) {}

std::string MouseButtonPressedEvent::toString() const {
    std::stringstream stream;
    stream << "MouseButtonPressedEvent: " << mouseButton;
    return stream.str();
}

MouseButtonReleasedEvent::MouseButtonReleasedEvent(size_t mouseButton) : MouseButtonEvent(mouseButton) {}

std::string MouseButtonReleasedEvent::toString() const {
    std::stringstream stream;
    stream << "MouseButtonReleasedEvent: " << mouseButton;
    return stream.str();
}
}