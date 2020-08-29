#ifndef _OPENGL_GRAPHICS_CONTEXT_HPP_
#define _OPENGL_GRAPHICS_CONTEXT_HPP_

#include "navia/core/Base.hpp"
#include "navia/renderer/GraphicsContext.hpp"
#include <GLFW/glfw3.h>

namespace Navia {
class OpenGLGraphicsContext : public GraphicsContext {
public:
    OpenGLGraphicsContext(GLFWwindow* window);

    void init() override;
    void swapBuffers() override;

private:
    GLFWwindow* window;
};
}

#endif