#include "navia/renderer/Renderer2D.hpp"
#include "navia/platform/opengl/OpenGLGraphicsContext.hpp"
#include <glad/glad.h>

namespace Navia {
OpenGLGraphicsContext::OpenGLGraphicsContext(GLFWwindow* window) : window(window) {
    NAVIA_CORE_ASSERT(window, "Window is nullptr!")
}

void OpenGLGraphicsContext::init() {
    NAVIA_PROFILE_FUNCTION();

    glfwMakeContextCurrent(window);
    auto result = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    NAVIA_CORE_ASSERT(result, "Failed to initialize GLAD!");

#ifdef NAVIA_ENABLE_ASSERTS
    int major;
    int minor;
    glGetIntegerv(GL_MAJOR_VERSION, &major);
    glGetIntegerv(GL_MINOR_VERSION, &minor);
    NAVIA_CORE_ASSERT(major > 4 || (major == 4 && minor >= 5), "Navia requires at least OpenGL v4.5!");
#endif
}

void OpenGLGraphicsContext::swapBuffers() {
    NAVIA_PROFILE_FUNCTION();

    glfwSwapBuffers(window);
}

Renderer2D::Renderer2DInfo Renderer2D::getInfo() {
    return Renderer2DInfo{ glGetString(GL_VENDOR), glGetString(GL_RENDERER), glGetString(GL_VERSION)};
}
}