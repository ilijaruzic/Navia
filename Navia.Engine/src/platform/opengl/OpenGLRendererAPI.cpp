#include "navia/platform/opengl/OpenGLRendererAPI.hpp"
#include <glad/glad.h>

namespace Navia {
void OpenGLRendererAPI::init() {
    NAVIA_PROFILE_FUNCTION();

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_DEPTH_TEST);
}

void OpenGLRendererAPI::shutdown() {
    NAVIA_PROFILE_FUNCTION();


}

void OpenGLRendererAPI::setViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) {
    glViewport(x, y, width, height);
}

void OpenGLRendererAPI::setClearColor(const glm::vec4& color) {
    glClearColor(color.r, color.g, color.b, color.a);
}

void OpenGLRendererAPI::clear() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void OpenGLRendererAPI::drawIndexed(Ref<VertexArray> vertexArray, uint32_t indexCount) {
    uint32_t count = indexCount ? vertexArray->getIndexBuffer()->getCount() : indexCount;
    glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);
}
}