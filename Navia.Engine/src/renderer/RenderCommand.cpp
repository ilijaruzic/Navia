#include "navia/renderer/RenderCommand.hpp"
#include "navia/platform/opengl/OpenGLRendererAPI.hpp"

namespace Navia {
RendererAPI* RenderCommand::rendererAPI = new OpenGLRendererAPI();

void RenderCommand::setClearColor(const glm::vec4& color) {
    rendererAPI->setClearColor(color);
}

void RenderCommand::clear() {
    rendererAPI->clear();
}

void RenderCommand::drawIndexed(Ref<VertexArray> vertexArray) {
    rendererAPI->drawIndexed(vertexArray);
}
}