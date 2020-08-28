#include "navia/platform/opengl/OpenGLGraphicsContext.hpp"
#include <glad/glad.h>

namespace Navia {
OpenGLGraphicsContext::OpenGLGraphicsContext(GLFWwindow* window) : window(window) {
    NAVIA_CORE_ASSERT(window, "Window is nullptr!")
}

void OpenGLGraphicsContext::init() {
    glfwMakeContextCurrent(window);
    auto result = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    NAVIA_CORE_ASSERT(result, "Failed to initialize GLAD!");

    NAVIA_CORE_INFO("OpenGL Information");
    NAVIA_CORE_INFO("==================");
    NAVIA_CORE_INFO("\tVendor: {0}", glGetString(GL_VENDOR));
    NAVIA_CORE_INFO("\tRenderer: {0}", glGetString(GL_RENDERER));
    NAVIA_CORE_INFO("\tVersion: {0}", glGetString(GL_VERSION));

#ifdef NAVIA_ENABLE_ASSERTS
    int major;
    int minor;
    glGetIntegerv(GL_MAJOR_VERSION, &major);
    glGetIntegerv(GL_MINOR_VERSION, &minor);
    NAVIA_CORE_ASSERT(major > 4 || (major == 4 && minor >= 5), "Navia requires at least OpenGL v4.5!");
#endif
}

void OpenGLGraphicsContext::swapBuffers() {
    glfwSwapBuffers(window);
}
}