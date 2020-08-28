#include "navia/renderer/Renderer2D.hpp"
#include "navia/renderer/IndexBuffer.hpp"
#include "navia/renderer/RenderCommand.hpp"
#include "navia/renderer/VertexArray.hpp"
#include "navia/renderer/VertexBuffer.hpp"
#include <glm/gtc/matrix_transform.hpp>

namespace Navia {
struct Renderer2DData {
    Ref<VertexArray> vertexArray;
    Ref<Shader> flatColorShader;
    Ref<Shader> textureShader;
};
static Renderer2DData* data;

void Renderer2D::init() {
    data = new Renderer2DData();

    data->vertexArray = VertexArray::create();

    float vertices[5 * 4]{
        -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
         0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
         0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
        -0.5f,  0.5f, 0.0f, 0.0f, 1.0f
    };
    Ref<VertexBuffer> vertexBuffer = VertexBuffer::create(vertices, sizeof(vertices));
    BufferLayout layout{
        { ShaderDatatype::Float3, "v_inPosition" },
        { ShaderDatatype::Float2, "v_inTextureCoords" },
    };
    vertexBuffer->setLayout(layout);
    data->vertexArray->addVertexBuffer(vertexBuffer);

    size_t indices[6]{
        0, 1, 2, 2, 3, 0
    };
    Ref<IndexBuffer> indexBuffer = IndexBuffer::create(indices, sizeof(indices) / sizeof(size_t));
    data->vertexArray->setIndexBuffer(indexBuffer);

    data->flatColorShader = Shader::create("assets/shaders/flatColor.glsl");
    data->textureShader = Shader::create("assets/shaders/texture.glsl");
    data->textureShader->bind();
    data->textureShader->setInt("f_uTexture", 0);
}

void Renderer2D::shutdown() {
    delete data;
}

void Renderer2D::beginScene(const OrthographicCamera& camera) {
    data->flatColorShader->bind();
    data->flatColorShader->setMat4("v_uViewProjection", camera.getViewProjectionMatrix());
    data->textureShader->bind();
    data->textureShader->setMat4("v_uViewProjection", camera.getViewProjectionMatrix());
}

void Renderer2D::endScene() {

}

void Renderer2D::drawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color) {
    drawQuad(glm::vec3{ position.x, position.y, 0.0f }, size, color);
}

void Renderer2D::drawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color) {
    data->flatColorShader->bind();
    data->flatColorShader->setFloat4("f_uColor", color);

    glm::mat4 transform = glm::translate(glm::mat4{ 1.0f }, position) * glm::scale(glm::mat4{ 1.0f }, glm::vec3{ size.x, size.y, 1.0f });
    data->flatColorShader->setMat4("v_uTransform", transform);

    data->vertexArray->bind();
    RenderCommand::drawIndexed(data->vertexArray);
}

void Renderer2D::drawQuad(const glm::vec2& position, const glm::vec2& size, Ref<Texture2D> texture) {
    drawQuad(glm::vec3{ position.x, position.y, 0.0f }, size, texture);
}

void Renderer2D::drawQuad(const glm::vec3& position, const glm::vec2& size, Ref<Texture2D> texture) {
    data->textureShader->bind();

    glm::mat4 transform = glm::translate(glm::mat4{ 1.0f }, position) * glm::scale(glm::mat4{ 1.0f }, glm::vec3{ size.x, size.y, 1.0f });
    data->textureShader->setMat4("v_uTransform", transform);

    texture->bind();

    data->vertexArray->bind();
    RenderCommand::drawIndexed(data->vertexArray);
}
}