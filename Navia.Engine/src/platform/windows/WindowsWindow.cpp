#include "navia/events/KeyEvent.hpp"
#include "navia/events/MouseEvent.hpp"
#include "navia/events/WindowEvent.hpp"
#include "navia/platform/opengl/OpenGLGraphicsContext.hpp"
#include "navia/platform/windows/WindowsWindow.hpp"

namespace Navia {
static bool glfwInitialized = false;

static void glfwErrorCallback(int errorCode, const char* description) {
    NAVIA_CORE_ERROR("GLFW_ERROR_{0}: {1}", errorCode, description);
}

Scope<Window> Window::create(const WindowProperties& properties) {
    return createScope<WindowsWindow>(properties);
}

WindowsWindow::WindowsWindow(const WindowProperties& properties) {
    NAVIA_PROFILE_FUNCTION();

    data.title = properties.title;
    data.width = properties.width;
    data.height = properties.height;

    NAVIA_CORE_INFO("Creating window '{0}' ({1}x{2})...", properties.title, properties.width, properties.height);

    if (!glfwInitialized) {
        NAVIA_PROFILE_SCOPE("Navia::WindowsWindow::WindowsWindow(const WindowProperties& properties) — initializing GLFW");

        auto result = glfwInit();
        NAVIA_CORE_ASSERT(result, "Failed to initialize GLFW!");
        glfwSetErrorCallback(glfwErrorCallback);
        glfwInitialized = true;
    }

    {
        NAVIA_PROFILE_SCOPE("Navia::WindowsWindow::WindowsWindow(const WindowProperties& properties) — creating GLFW window");

        window = glfwCreateWindow(properties.width, properties.height, data.title.c_str(), nullptr, nullptr);
    }
    context = new OpenGLGraphicsContext(window);
    context->init();

    glfwSetWindowUserPointer(window, &data);
    setVSync(true);
    setEventCallbacks();
}

WindowsWindow::~WindowsWindow() {
    NAVIA_PROFILE_FUNCTION();

    glfwDestroyWindow(window);
    glfwTerminate();
}

uint32_t WindowsWindow::getWidth() const {
    return data.width;
}

uint32_t WindowsWindow::getHeight() const {
    return data.height;
}

void* WindowsWindow::getNativeWindow() const {
    return window;
}

void WindowsWindow::onUpdate() {
    NAVIA_PROFILE_FUNCTION();

    glfwPollEvents();
    context->swapBuffers();
}

void WindowsWindow::setEventCallback(const EventCallbackType& callback) {
    data.callback = callback;
}

void WindowsWindow::setVSync(bool enabled) {
    NAVIA_PROFILE_FUNCTION();

    if (enabled) {
        glfwSwapInterval(1);
    }
    else {
        glfwSwapInterval(0);
    }
    data.vsync = enabled;
}

bool WindowsWindow::isVSync() const {
    return data.vsync;
}

void WindowsWindow::setEventCallbacks() const {
    glfwSetWindowSizeCallback(window, [](GLFWwindow* glfwWindow, int width, int height) {
        WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(glfwWindow));
        data.width = width;
        data.height = height;

        WindowResizeEvent event{ static_cast<uint32_t>(width), static_cast<uint32_t>(height) };
        data.callback(event);
    });

    glfwSetWindowCloseCallback(window, [](GLFWwindow* glfwWindow) {
        WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(glfwWindow));

        WindowCloseEvent event{};
        data.callback(event);
    });

    glfwSetKeyCallback(window, [](GLFWwindow* glfwWindow, int key, int scancode, int action, int mods) {
        WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(glfwWindow));

        switch (action) {
            case GLFW_PRESS:
            {
                KeyPressedEvent event{ static_cast<uint32_t>(key), 0 };
                data.callback(event);
                break;
            }
            case GLFW_RELEASE:
            {
                KeyReleasedEvent event{ static_cast<uint32_t>(key) };
                data.callback(event);
                break;
            }
            case GLFW_REPEAT:
            {
                KeyPressedEvent event{ static_cast<uint32_t>(key), 1 };
                data.callback(event);
                break;
            }
        }
    });

    glfwSetCharCallback(window, [](GLFWwindow* glfwWindow, unsigned key) {
        WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(glfwWindow));

        KeyTypedEvent event{ key };
        data.callback(event);
    });

    glfwSetCursorPosCallback(window, [](GLFWwindow* glfwWindow, double x, double y) {
        WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(glfwWindow));

        MouseMovedEvent event{ static_cast<float>(x), static_cast<float>(y) };
        data.callback(event);
    });

    glfwSetScrollCallback(window, [](GLFWwindow* glfwWindow, double xOffset, double yOffset) {
        WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(glfwWindow));

        MouseScrolledEvent event{ static_cast<float>(xOffset), static_cast<float>(yOffset) };
        data.callback(event);
    });

    glfwSetMouseButtonCallback(window, [](GLFWwindow* glfwWindow, int button, int action, int mods) {
        WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(glfwWindow));

        switch (action) {
            case GLFW_PRESS:
            {
                MouseButtonPressedEvent event{ static_cast<uint32_t>(button) };
                data.callback(event);
                break;
            }
            case GLFW_RELEASE:
            {
                MouseButtonReleasedEvent event{ static_cast<uint32_t>(button) };
                data.callback(event);
                break;
            }
        }
    });
}
}