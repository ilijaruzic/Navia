#include "navia/renderer/Renderer2D.hpp"
#include "navia/renderer/IndexBuffer.hpp"
#include "navia/renderer/RenderCommand.hpp"
#include "navia/renderer/VertexArray.hpp"
#include "navia/renderer/VertexBuffer.hpp"
#include "navia/platform/opengl/OpenGLShader.hpp"

namespace Navia {
struct Renderer2DData {
    Ref<VertexArray> vertexArray;
    Ref<Shader> shader;
};
static Renderer2DData* data;

void Renderer2D::init() {
    data = new Renderer2DData();

    data->vertexArray = VertexArray::create();

    float vertices[3 * 4]{
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.5f,  0.5f, 0.0f,
        -0.5f,  0.5f, 0.0f
    };
    Ref<VertexBuffer> vertexBuffer = VertexBuffer::create(vertices, sizeof(vertices));
    BufferLayout layout{
        { ShaderDatatype::Float3, "v_inPosition" }
    };
    vertexBuffer->setLayout(layout);
    data->vertexArray->addVertexBuffer(vertexBuffer);

    size_t indices[6]{
        0, 1, 2, 2, 3, 0
    };
    Ref<IndexBuffer> indexBuffer = IndexBuffer::create(indices, sizeof(indices) / sizeof(size_t));
    data->vertexArray->setIndexBuffer(indexBuffer);

    data->shader = Shader::create("assets/shaders/flatColor.glsl");
}

void Renderer2D::shutdown() {
    delete data;
}

void Renderer2D::beginScene(const OrthographicCamera& camera) {
    std::dynamic_pointer_cast<Navia::OpenGLShader>(data->shader)->bind();
    std::dynamic_pointer_cast<Navia::OpenGLShader>(data->shader)->uploadUniformMat4("v_uViewProjection", camera.getViewProjectionMatrix());
    std::dynamic_pointer_cast<Navia::OpenGLShader>(data->shader)->uploadUniformMat4("v_uTransform", glm::mat4{ 1.0f });
}

void Renderer2D::endScene() {

}

void Renderer2D::drawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color) {
    drawQuad(glm::vec3{ position.x, position.y, 0.0f }, size, color);
}

void Renderer2D::drawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color) {
    std::dynamic_pointer_cast<Navia::OpenGLShader>(data->shader)->bind();
    std::dynamic_pointer_cast<Navia::OpenGLShader>(data->shader)->uploadUniformFloat4("f_uColor", color);
    data->vertexArray->bind();
    RenderCommand::drawIndexed(data->vertexArray);
}
}