#ifndef _WINDOW_HPP_
#define _WINDOW_HPP_

#include "navia/events/Event.hpp"

namespace Navia {
struct WindowProperties {
    std::string title;
    size_t width;
    size_t height;

    WindowProperties(const std::string& title = "Navia Engine", size_t width = 1280, size_t height = 720);
};

class Window {
public:
    using EventCallbackType = std::function<void(Event&)>;

    static Window* create(const WindowProperties& properties = WindowProperties{});
    virtual ~Window() = default;

    virtual size_t getWidth() const = 0;
    virtual size_t getHeight() const = 0;
    virtual void* getNativeWindow() const = 0;

    virtual void onUpdate() = 0;

    virtual void setEventCallback(const EventCallbackType& callback) = 0;
    virtual void setVSync(bool enabled) = 0;
    virtual bool isVSync() const = 0;
};
}

#endif