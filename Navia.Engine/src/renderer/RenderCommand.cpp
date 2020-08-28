#include "navia/renderer/RenderCommand.hpp"
#include "navia/platform/opengl/OpenGLRendererAPI.hpp"

namespace Navia {
RendererAPI* RenderCommand::rendererAPI = new OpenGLRendererAPI();

void RenderCommand::init() {
    rendererAPI->init();
}

void RenderCommand::shutdown() {
    rendererAPI->shutdown();
}

void RenderCommand::setViewport(size_t x, size_t y, size_t width, size_t height) {
    rendererAPI->setViewport(x, y, width, height);
}

void RenderCommand::setClearColor(const glm::vec4& color) {
    rendererAPI->setClearColor(color);
}

void RenderCommand::clear() {
    rendererAPI->clear();
}

void RenderCommand::drawIndexed(Ref<VertexArray> vertexArray, size_t indexCount) {
    rendererAPI->drawIndexed(vertexArray, indexCount);
}
}