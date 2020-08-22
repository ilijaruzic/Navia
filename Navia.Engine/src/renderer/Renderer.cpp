#include "navia/renderer/RenderCommand.hpp"
#include "navia/renderer/Renderer.hpp"
#include "navia/platform/opengl/OpenGLShader.hpp"

namespace Navia {
Renderer::SceneData* Renderer::data = new SceneData();

void Renderer::init() {
    RenderCommand::init();
}

RendererAPI::APIVendor Renderer::getRendererAPI() {
    return RendererAPI::getAPIVendor();
}

void Renderer::beginScene(OrthographicCamera& camera) {
    data->viewProjectionMatrix = camera.getViewProjectionMatrix();
}

void Renderer::endScene() {}

void Renderer::submit(Ref<Shader> shader, Ref<VertexArray> vertexArray, const glm::mat4& transform) {
    shader->bind();
    std::dynamic_pointer_cast<OpenGLShader>(shader)->uploadUniformMat4("v_uViewProjection", data->viewProjectionMatrix);
    std::dynamic_pointer_cast<OpenGLShader>(shader)->uploadUniformMat4("v_uTransform", transform);
    vertexArray->bind();
    RenderCommand::drawIndexed(vertexArray);
}
}