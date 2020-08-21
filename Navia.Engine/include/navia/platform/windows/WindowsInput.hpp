#ifndef _WINDOWS_INPUT_HPP_
#define _WINDOWS_INPUT_HPP_

#include <cstddef>
#include <utility>
#include "Input.hpp"

namespace Navia {
class WindowsInput : public Input {
protected:
    bool isMouseButtonPressedImpl(size_t button) override;
    std::pair<float, float> getMousePositionImpl() override;
    float getMouseXImpl() override;
    float getMouseYImpl() override;

    bool isKeyPressedImpl(size_t keyCode) override;
};
}

#endif