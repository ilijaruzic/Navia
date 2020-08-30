#ifndef _INPUT_HPP_
#define _INPUT_HPP_

#include "navia/core/Base.hpp"
#include "navia/core/KeyCodes.hpp"
#include "navia/core/MouseCodes.hpp"

namespace Navia {
class Input {
public:
    static bool isMouseButtonPressed(uint32_t button);
    static std::pair<float, float> getMousePosition();
    static float getMouseX();
    static float getMouseY();

    static bool isKeyPressed(uint32_t keyCode);
};
}

#endif