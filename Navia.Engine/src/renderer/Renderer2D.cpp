#include "navia/renderer/Renderer2D.hpp"
#include "navia/renderer/IndexBuffer.hpp"
#include "navia/renderer/RenderCommand.hpp"
#include "navia/renderer/VertexArray.hpp"
#include "navia/renderer/VertexBuffer.hpp"
#include "navia/renderer/Texture.hpp"
#include <glm/gtc/matrix_transform.hpp>

namespace Navia {
struct Renderer2DData {
    Ref<VertexArray> vertexArray;
    Ref<Shader> shader;
    Ref<Texture2D> whiteTexture;
};
static Renderer2DData* data;

void Renderer2D::init() {
    NAVIA_PROFILE_FUNCTION();

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

    data->whiteTexture = Texture2D::create(1, 1);
    size_t whiteTextureData = 0xffffffff;
    data->whiteTexture->setData(&whiteTextureData, sizeof(size_t));

    data->shader = Shader::create("assets/shaders/shader.glsl");
    data->shader->bind();
    data->shader->setInt("f_uTexture", 0);
}

void Renderer2D::shutdown() {
    NAVIA_PROFILE_FUNCTION();

    delete data;
}

void Renderer2D::beginScene(const OrthographicCamera& camera) {
    NAVIA_PROFILE_FUNCTION();

    data->shader->bind();
    data->shader->setMat4("v_uViewProjection", camera.getViewProjectionMatrix());
}

void Renderer2D::endScene() {
    NAVIA_PROFILE_FUNCTION();


}

void Renderer2D::drawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color) {
    drawQuad(glm::vec3{ position.x, position.y, 0.0f }, size, color);
}

void Renderer2D::drawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color) {
    NAVIA_PROFILE_FUNCTION();

    data->shader->setFloat4("f_uColor", color);
    data->shader->setFloat("f_uTilingFactor", 1.0f);
    data->whiteTexture->bind();

    glm::mat4 transform =
            glm::translate(glm::mat4{ 1.0f }, position) *
            glm::scale(glm::mat4{ 1.0f }, glm::vec3{ size.x, size.y, 1.0f });
    data->shader->setMat4("v_uTransform", transform);

    data->vertexArray->bind();
    RenderCommand::drawIndexed(data->vertexArray);
}

void Renderer2D::drawQuad(const glm::vec2& position, const glm::vec2& size, Ref<Texture2D> texture, float tilingFactor, const glm::vec4& tintColor) {
    drawQuad(glm::vec3{ position.x, position.y, 0.0f }, size, texture, tilingFactor, tintColor);
}

void Renderer2D::drawQuad(const glm::vec3& position, const glm::vec2& size, Ref<Texture2D> texture, float tilingFactor, const glm::vec4& tintColor) {
    NAVIA_PROFILE_FUNCTION();

    data->shader->setFloat4("f_uColor", tintColor);
    data->shader->setFloat("f_uTilingFactor", tilingFactor);
    texture->bind();

    glm::mat4 transform =
            glm::translate(glm::mat4{ 1.0f }, position) *
            glm::scale(glm::mat4{ 1.0f }, glm::vec3{ size.x, size.y, 1.0f });
    data->shader->setMat4("v_uTransform", transform);

    data->vertexArray->bind();
    RenderCommand::drawIndexed(data->vertexArray);
}

void Renderer2D::drawRotatedQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const glm::vec4& color) {
    drawRotatedQuad(glm::vec3{ position.x, position.y, 0.0f }, size, rotation, color);
}

void Renderer2D::drawRotatedQuad(const glm::vec3& position, const glm::vec2& size, float rotation, const glm::vec4& color) {
    NAVIA_PROFILE_FUNCTION();

    data->shader->setFloat4("f_uColor", color);
    data->shader->setFloat("f_uTilingFactor", 1.0f);
    data->whiteTexture->bind();

    glm::mat4 transform =
            glm::translate(glm::mat4{ 1.0f }, position) *
            glm::rotate(glm::mat4{ 1.0f }, rotation, glm::vec3{ 0.0f, 0.0f, 1.0f }) *
            glm::scale(glm::mat4{ 1.0f }, glm::vec3{ size.x, size.y, 1.0f });
    data->shader->setMat4("v_uTransform", transform);

    data->vertexArray->bind();
    RenderCommand::drawIndexed(data->vertexArray);
}

void Renderer2D::drawRotatedQuad(const glm::vec2& position, const glm::vec2& size, float rotation, Ref<Texture2D> texture, float tilingFactor, const glm::vec4& tintColor) {
    drawRotatedQuad(glm::vec3{ position.x, position.y, 0.0f }, size, rotation, texture, tilingFactor, tintColor);
}

void Renderer2D::drawRotatedQuad(const glm::vec3& position, const glm::vec2& size, float rotation, Ref<Texture2D> texture, float tilingFactor, const glm::vec4& tintColor) {
    NAVIA_PROFILE_FUNCTION();

    data->shader->setFloat4("f_uColor", tintColor);
    data->shader->setFloat("f_uTilingFactor", tilingFactor);
    texture->bind();

    glm::mat4 transform =
            glm::translate(glm::mat4{ 1.0f }, position) *
            glm::rotate(glm::mat4{ 1.0f }, rotation, glm::vec3{ 0.0f, 0.0f, 1.0f }) *
            glm::scale(glm::mat4{ 1.0f }, glm::vec3{ size.x, size.y, 1.0f });
    data->shader->setMat4("v_uTransform", transform);

    data->vertexArray->bind();
    RenderCommand::drawIndexed(data->vertexArray);
}
}