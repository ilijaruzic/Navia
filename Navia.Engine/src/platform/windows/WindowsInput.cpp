#include "navia/core/Application.hpp"
#include "navia/core/Input.hpp"
#include <GLFW/glfw3.h>

namespace Navia {
bool Input::isMouseButtonPressed(uint32_t button) {
    auto window = static_cast<GLFWwindow*>(Application::getInstance().getWindow().getNativeWindow());
    auto result = glfwGetMouseButton(window, button);
    return result == GLFW_PRESS;
}

std::pair<float, float> Input::getMousePosition() {
    auto window = static_cast<GLFWwindow*>(Application::getInstance().getWindow().getNativeWindow());
    double x, y;
    glfwGetCursorPos(window, &x, &y);
    return { static_cast<float>(x), static_cast<float>(y) };
}

float Input::getMouseX() {
    auto[x, y] = getMousePosition();
    return x;
}

float Input::getMouseY() {
    auto[x, y] = getMousePosition();
    return y;
}

bool Input::isKeyPressed(uint32_t keyCode) {
    auto window = static_cast<GLFWwindow*>(Application::getInstance().getWindow().getNativeWindow());
    auto result = glfwGetKey(window, keyCode);
    return result == GLFW_PRESS || result == GLFW_REPEAT;
}
}