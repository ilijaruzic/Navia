#include "navia/core/Application.hpp"
#include "navia/platform/windows/WindowsInput.hpp"
#include <GLFW/glfw3.h>

namespace Navia {
Input* Input::instance = new WindowsInput();

bool WindowsInput::isMouseButtonPressedImpl(size_t button) {
    auto window = static_cast<GLFWwindow*>(Application::getInstance().getWindow().getNativeWindow());
    auto result = glfwGetMouseButton(window, button);
    return result == GLFW_PRESS;
}

std::pair<float, float> WindowsInput::getMousePositionImpl() {
    auto window = static_cast<GLFWwindow*>(Application::getInstance().getWindow().getNativeWindow());
    double x, y;
    glfwGetCursorPos(window, &x, &y);
    return { x, y };
}

float WindowsInput::getMouseXImpl() {
    auto[x, y] = getMousePositionImpl();
    return x;
}

float WindowsInput::getMouseYImpl() {
    auto[x, y] = getMousePositionImpl();
    return y;
}

bool WindowsInput::isKeyPressedImpl(size_t keyCode) {
    auto window = static_cast<GLFWwindow*>(Application::getInstance().getWindow().getNativeWindow());
    auto result = glfwGetKey(window, keyCode);
    return result == GLFW_PRESS || result == GLFW_REPEAT;
}
}