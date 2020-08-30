#ifndef _WINDOWS_WINDOW_HPP_
#define _WINDOWS_WINDOW_HPP_

#include "navia/core/Window.hpp"
#include "navia/renderer/GraphicsContext.hpp"
#include <GLFW/glfw3.h>

namespace Navia {
class WindowsWindow : public Window {
public:
    WindowsWindow(const WindowProperties& properties);
    ~WindowsWindow();

    uint32_t getWidth() const override;
    uint32_t getHeight() const override;
    void* getNativeWindow() const override;

    void onUpdate() override;

    void setEventCallback(const EventCallbackType& callback) override;
    void setVSync(bool enabled) override;
    bool isVSync() const override;

private:
    GLFWwindow* window;
    GraphicsContext* context;

    struct WindowData {
        std::string title;
        uint32_t width;
        uint32_t height;
        bool vsync;
        EventCallbackType callback;
    };
    WindowData data;

    void setEventCallbacks() const;
};
}

#endif