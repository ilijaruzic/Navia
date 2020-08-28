#include "navia/core/Input.hpp"

namespace Navia {
bool Input::isMouseButtonPressed(size_t button) {
    return instance->isMouseButtonPressedImpl(button);
}

std::pair<float, float> Input::getMousePosition() {
    return instance->getMousePositionImpl();
}

float Input::getMouseX() {
    return instance->getMouseXImpl();
}

float Input::getMouseY() {
    return instance->getMouseYImpl();
}

bool Input::isKeyPressed(size_t keyCode) {
    return instance->isKeyPressedImpl(keyCode);
}
}