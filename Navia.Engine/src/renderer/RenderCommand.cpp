#include "navia/renderer/RenderCommand.hpp"
#include "navia/platform/opengl/OpenGLRendererAPI.hpp"

namespace Navia {
Scope<RendererAPI> RenderCommand::rendererAPI = createScope<OpenGLRendererAPI>();

void RenderCommand::init() {
    rendererAPI->init();
}

void RenderCommand::shutdown() {
    rendererAPI->shutdown();
}

void RenderCommand::setViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) {
    rendererAPI->setViewport(x, y, width, height);
}

void RenderCommand::setClearColor(const glm::vec4& color) {
    rendererAPI->setClearColor(color);
}

void RenderCommand::clear() {
    rendererAPI->clear();
}

void RenderCommand::drawIndexed(Ref<VertexArray> vertexArray, uint32_t indexCount) {
    rendererAPI->drawIndexed(vertexArray, indexCount);
}
}