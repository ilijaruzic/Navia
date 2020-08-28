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

void OpenGLRendererAPI::setViewport(size_t x, size_t y, size_t width, size_t height) {
    glViewport(x, y, width, height);
}

void OpenGLRendererAPI::setClearColor(const glm::vec4& color) {
    glClearColor(color.r, color.g, color.b, color.a);
}

void OpenGLRendererAPI::clear() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void OpenGLRendererAPI::drawIndexed(Ref<VertexArray> vertexArray, size_t indexCount) {
    size_t count = indexCount ? vertexArray->getIndexBuffer()->getCount() : indexCount;
    glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);
}
}