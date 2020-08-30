#include "navia/events/WindowEvent.hpp"

namespace Navia {
WindowResizeEvent::WindowResizeEvent(uint32_t width, uint32_t height) : width(width), height(height) {}

uint32_t WindowResizeEvent::getWidth() const {
    return width;
}

uint32_t WindowResizeEvent::getHeight() const {
    return height;
}

std::string WindowResizeEvent::toString() const {
    std::stringstream stream;
    stream << "WindowResizeEvent: " << width << "x" << height;
    return stream.str();
}
}