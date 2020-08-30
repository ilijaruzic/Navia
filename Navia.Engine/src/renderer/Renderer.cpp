#include "navia/renderer/RenderCommand.hpp"
#include "navia/renderer/Renderer.hpp"
#include "navia/renderer/Renderer2D.hpp"
#include "navia/platform/opengl/OpenGLShader.hpp"

namespace Navia {
Scope<Renderer::SceneData> Renderer::data = createScope<Renderer::SceneData>();

void Renderer::init() {
    NAVIA_PROFILE_FUNCTION();

    RenderCommand::init();
    Renderer2D::init();
}

void Renderer::shutdown() {
    NAVIA_PROFILE_FUNCTION();

    RenderCommand::shutdown();
    Renderer2D::shutdown();
}

void Renderer::onWindowResize(uint32_t width, uint32_t height) {
    RenderCommand::setViewport(0, 0, width, height);
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
    shader->setMat4("v_uViewProjection", data->viewProjectionMatrix);
    shader->setMat4("v_uTransform", transform);
    vertexArray->bind();
    RenderCommand::drawIndexed(vertexArray);
}
}