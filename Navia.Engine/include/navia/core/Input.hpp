#ifndef _INPUT_HPP_
#define _INPUT_HPP_

namespace Navia {
class Input {
public:
    Input(const Input&) = delete;
    Input& operator=(const Input&) = delete;

    static bool isMouseButtonPressed(size_t button);
    static std::pair<float, float> getMousePosition();
    static float getMouseX();
    static float getMouseY();

    static bool isKeyPressed(size_t keyCode);

protected:
    Input() = default;

    virtual bool isMouseButtonPressedImpl(size_t button) = 0;
    virtual std::pair<float, float> getMousePositionImpl() = 0;
    virtual float getMouseXImpl() = 0;
    virtual float getMouseYImpl() = 0;

    virtual bool isKeyPressedImpl(size_t keyCode) = 0;

private:
    static Input* instance;
};
}

#endif