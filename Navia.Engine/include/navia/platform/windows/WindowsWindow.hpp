#ifndef _WINDOWS_WINDOW_HPP_
#define _WINDOWS_WINDOW_HPP_

#include "Window.hpp"
#include <GLFW/glfw3.h>

namespace Navia {
class WindowsWindow : public Window {
public:
    WindowsWindow(const WindowProperties& properties);
    ~WindowsWindow();

    size_t getWidth() const override;
    size_t getHeight() const override;
    void* getNativeWindow() const override;

    void onUpdate() override;

    void setEventCallback(const EventCallbackType& callback) override;
    void setVSync(bool enabled) override;
    bool isVSync() const override;

private:
    GLFWwindow* window;

    struct WindowData {
        std::string title;
        size_t width;
        size_t height;
        bool vsync;
        EventCallbackType callback;
    };
    WindowData data;

    void setEventCallbacks() const;
};
}

#endif