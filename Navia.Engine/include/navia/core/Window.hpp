#ifndef _WINDOW_HPP_
#define _WINDOW_HPP_

#include "navia/events/Event.hpp"

namespace Navia {
struct WindowProperties {
    std::string title;
    uint32_t width;
    uint32_t height;

    WindowProperties(const std::string& title = "Navia Engine", uint32_t width = 1280, uint32_t height = 720);
};

class Window {
public:
    using EventCallbackType = std::function<void(Event&)>;

    static Scope<Window> create(const WindowProperties& properties = WindowProperties{});
    virtual ~Window() = default;

    virtual uint32_t getWidth() const = 0;
    virtual uint32_t getHeight() const = 0;
    virtual void* getNativeWindow() const = 0;

    virtual void onUpdate() = 0;

    virtual void setEventCallback(const EventCallbackType& callback) = 0;
    virtual void setVSync(bool enabled) = 0;
    virtual bool isVSync() const = 0;
};
}

#endif