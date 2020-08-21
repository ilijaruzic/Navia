#include "WindowEvent.hpp"

namespace Navia {
WindowResizeEvent::WindowResizeEvent(size_t width, size_t height) : width(width), height(height) {}

size_t WindowResizeEvent::getWidth() const {
    return width;
}

size_t WindowResizeEvent::getHeight() const {
    return height;
}

std::string WindowResizeEvent::toString() const {
    std::stringstream stream;
    stream << "WindowResizeEvent: " << width << "x" << height;
    return stream.str();
}
}