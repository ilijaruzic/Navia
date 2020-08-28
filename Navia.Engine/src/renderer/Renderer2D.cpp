#include "navia/renderer/Renderer2D.hpp"
#include "navia/renderer/IndexBuffer.hpp"
#include "navia/renderer/RenderCommand.hpp"
#include "navia/renderer/VertexArray.hpp"
#include "navia/renderer/VertexBuffer.hpp"
#include "navia/renderer/Texture.hpp"
#include <glm/gtc/matrix_transform.hpp>

namespace Navia {
struct QuadVertex {
    glm::vec3 position;
    glm::vec4 color;
    glm::vec2 textureCoords;
    float textureIndex;
    float tilingFactor;
};

struct Renderer2DData {
    static constexpr size_t MaxQuadsCount{ 10000 };
    static constexpr size_t MaxVerticesCount{ MaxQuadsCount * 4 };
    static constexpr size_t MaxIndicesCount{ MaxQuadsCount * 6 };
    static constexpr size_t MaxTextureSlotsCount{ 32 };

    Ref<VertexArray> quadVertexArray;
    Ref<VertexBuffer> quadVertexBuffer;
    Ref<Shader> shader;
    Ref<Texture2D> whiteTexture;

    size_t quadIndexCount{ 0 };
    QuadVertex* quadVertexBufferBase{ nullptr };
    QuadVertex* quadVertexBufferPtr{ nullptr };

    std::array<Ref<Texture2D>, MaxTextureSlotsCount> textureSlots;
    size_t textureSlotIndex{ 1 };
};
static Renderer2DData data;

void Renderer2D::init() {
    NAVIA_PROFILE_FUNCTION();

    data.quadVertexArray = VertexArray::create();

    data.quadVertexBuffer = VertexBuffer::create(data.MaxVerticesCount * sizeof(QuadVertex));
    data.quadVertexBuffer->setLayout(BufferLayout{
        { ShaderDatatype::Float3, "v_inPosition" },
        { ShaderDatatype::Float4, "v_inColor" },
        { ShaderDatatype::Float2, "v_inTextureCoords" },
        { ShaderDatatype::Float, "v_inTextureIndex" },
        { ShaderDatatype::Float, "v_inTilingFactor" },
    });
    data.quadVertexArray->addVertexBuffer(data.quadVertexBuffer);

    data.quadVertexBufferBase = new QuadVertex[data.MaxVerticesCount];

    size_t* quadIndices = new size_t[data.MaxIndicesCount];
    size_t offset{ 0 };
    for (size_t i = 0; i < data.MaxIndicesCount; i += 6) {
        quadIndices[i + 0] = offset + 0;
        quadIndices[i + 1] = offset + 1;
        quadIndices[i + 2] = offset + 2;
        quadIndices[i + 3] = offset + 2;
        quadIndices[i + 4] = offset + 3;
        quadIndices[i + 5] = offset + 0;
        offset += 4;
    }
    Ref<IndexBuffer> quadIndexBuffer = IndexBuffer::create(quadIndices, data.MaxIndicesCount);
    data.quadVertexArray->setIndexBuffer(quadIndexBuffer);
    delete[] quadIndices;

    data.whiteTexture = Texture2D::create(1, 1);
    size_t whiteTextureData = 0xffffffff;
    data.whiteTexture->setData(&whiteTextureData, sizeof(size_t));

    int samplers[data.MaxTextureSlotsCount];
    for (size_t i = 0; i < data.MaxTextureSlotsCount; ++i) {
        samplers[i] = i;
    }
    data.shader = Shader::create("assets/shaders/shader.glsl");
    data.shader->bind();
    data.shader->setIntArray("f_uTextures", samplers, data.MaxTextureSlotsCount);

    data.textureSlots[0] = data.whiteTexture;
}

void Renderer2D::shutdown() {
    NAVIA_PROFILE_FUNCTION();


}

void Renderer2D::beginScene(const OrthographicCamera& camera) {
    NAVIA_PROFILE_FUNCTION();

    data.shader->bind();
    data.shader->setMat4("v_uViewProjection", camera.getViewProjectionMatrix());

    data.quadIndexCount = 0;
    data.quadVertexBufferPtr = data.quadVertexBufferBase;

    data.textureSlotIndex = 1;
}

void Renderer2D::endScene() {
    NAVIA_PROFILE_FUNCTION();

    size_t dataSize = (uint8_t*)data.quadVertexBufferPtr - (uint8_t*)data.quadVertexBufferBase;
    data.quadVertexBuffer->setData(data.quadVertexBufferBase, dataSize);
    flush();
}

void Renderer2D::flush() {
    NAVIA_PROFILE_FUNCTION();

    for (size_t i = 0; i < data.textureSlotIndex; ++i) {
        data.textureSlots[i]->bind(i);
    }
    RenderCommand::drawIndexed(data.quadVertexArray, data.quadIndexCount);
}

void Renderer2D::drawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color) {
    drawQuad(glm::vec3{ position.x, position.y, 0.0f }, size, color);
}

void Renderer2D::drawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color) {
    NAVIA_PROFILE_FUNCTION();

    constexpr float textureIndex{ 0.0f };
    constexpr float tilingFactor{ 1.0f };

    data.quadVertexBufferPtr->position = position;
    data.quadVertexBufferPtr->color = color;
    data.quadVertexBufferPtr->textureCoords = glm::vec2{ 0.0f, 0.0f };
    data.quadVertexBufferPtr->textureIndex = textureIndex;
    data.quadVertexBufferPtr->tilingFactor = tilingFactor;
    ++data.quadVertexBufferPtr;

    data.quadVertexBufferPtr->position = glm::vec3{ position.x + size.x, position.y, 0.0f };
    data.quadVertexBufferPtr->color = color;
    data.quadVertexBufferPtr->textureCoords = glm::vec2{ 1.0f, 0.0f };
    data.quadVertexBufferPtr->textureIndex = textureIndex;
    data.quadVertexBufferPtr->tilingFactor = tilingFactor;
    ++data.quadVertexBufferPtr;

    data.quadVertexBufferPtr->position = glm::vec3{ position.x + size.x, position.y + size.y, 0.0f };
    data.quadVertexBufferPtr->color = color;
    data.quadVertexBufferPtr->textureCoords = glm::vec2{ 1.0f, 1.0f };
    data.quadVertexBufferPtr->textureIndex = textureIndex;
    data.quadVertexBufferPtr->tilingFactor = tilingFactor;
    ++data.quadVertexBufferPtr;

    data.quadVertexBufferPtr->position = glm::vec3{ position.x, position.y + size.y, 0.0f };
    data.quadVertexBufferPtr->color = color;
    data.quadVertexBufferPtr->textureCoords = glm::vec2{ 1.0f, 0.0f };
    data.quadVertexBufferPtr->textureIndex = textureIndex;
    data.quadVertexBufferPtr->tilingFactor = tilingFactor;
    ++data.quadVertexBufferPtr;

    data.quadIndexCount += 6;

    // data.shader->setFloat("f_uTilingFactor", 1.0f);
    // data.whiteTexture->bind();
    //
    // glm::mat4 transform =
    //         glm::translate(glm::mat4{ 1.0f }, position) *
    //         glm::scale(glm::mat4{ 1.0f }, glm::vec3{ size.x, size.y, 1.0f });
    // data.shader->setMat4("v_uTransform", transform);
    //
    // data.quadVertexArray->bind();
    // RenderCommand::drawIndexed(data.quadVertexArray);
}

void Renderer2D::drawQuad(const glm::vec2& position, const glm::vec2& size, Ref<Texture2D> texture, float tilingFactor, const glm::vec4& tintColor) {
    drawQuad(glm::vec3{ position.x, position.y, 0.0f }, size, texture, tilingFactor, tintColor);
}

void Renderer2D::drawQuad(const glm::vec3& position, const glm::vec2& size, Ref<Texture2D> texture, float tilingFactor, const glm::vec4& tintColor) {
    NAVIA_PROFILE_FUNCTION();

    constexpr glm::vec4 color{ 1.0f };

    float textureIndex{ 0.0f };
    for (size_t i = 1; i < data.textureSlotIndex; ++i) {
        if (*data.textureSlots[i] == *texture)  {
            textureIndex = static_cast<float>(i);
            break;
        }
    }
    if (textureIndex == 0.0f) {
        textureIndex = static_cast<float>(data.textureSlotIndex);
        data.textureSlots[data.textureSlotIndex++] = texture;
    }

    data.quadVertexBufferPtr->position = position;
    data.quadVertexBufferPtr->color = color;
    data.quadVertexBufferPtr->textureCoords = glm::vec2{ 0.0f, 0.0f };
    data.quadVertexBufferPtr->textureIndex = textureIndex;
    data.quadVertexBufferPtr->tilingFactor = tilingFactor;
    ++data.quadVertexBufferPtr;

    data.quadVertexBufferPtr->position = glm::vec3{ position.x + size.x, position.y, 0.0f };
    data.quadVertexBufferPtr->color = color;
    data.quadVertexBufferPtr->textureCoords = glm::vec2{ 1.0f, 0.0f };
    data.quadVertexBufferPtr->textureIndex = textureIndex;
    data.quadVertexBufferPtr->tilingFactor = tilingFactor;
    ++data.quadVertexBufferPtr;

    data.quadVertexBufferPtr->position = glm::vec3{ position.x + size.x, position.y + size.y, 0.0f };
    data.quadVertexBufferPtr->color = color;
    data.quadVertexBufferPtr->textureCoords = glm::vec2{ 1.0f, 1.0f };
    data.quadVertexBufferPtr->textureIndex = textureIndex;
    data.quadVertexBufferPtr->tilingFactor = tilingFactor;
    ++data.quadVertexBufferPtr;

    data.quadVertexBufferPtr->position = glm::vec3{ position.x, position.y + size.y, 0.0f };
    data.quadVertexBufferPtr->color = color;
    data.quadVertexBufferPtr->textureCoords = glm::vec2{ 1.0f, 0.0f };
    data.quadVertexBufferPtr->textureIndex = textureIndex;
    data.quadVertexBufferPtr->tilingFactor = tilingFactor;
    ++data.quadVertexBufferPtr;

    data.quadIndexCount += 6;

    // data.shader->setFloat4("f_uColor", tintColor);
    // data.shader->setFloat("f_uTilingFactor", tilingFactor);
    // texture->bind();
    //
    // glm::mat4 transform =
    //         glm::translate(glm::mat4{ 1.0f }, position) *
    //         glm::scale(glm::mat4{ 1.0f }, glm::vec3{ size.x, size.y, 1.0f });
    // data.shader->setMat4("v_uTransform", transform);
    //
    // data.quadVertexArray->bind();
    // RenderCommand::drawIndexed(data.quadVertexArray);
}

void Renderer2D::drawRotatedQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const glm::vec4& color) {
    drawRotatedQuad(glm::vec3{ position.x, position.y, 0.0f }, size, rotation, color);
}

void Renderer2D::drawRotatedQuad(const glm::vec3& position, const glm::vec2& size, float rotation, const glm::vec4& color) {
    NAVIA_PROFILE_FUNCTION();

    data.shader->setFloat4("f_uColor", color);
    data.shader->setFloat("f_uTilingFactor", 1.0f);
    data.whiteTexture->bind();

    glm::mat4 transform =
            glm::translate(glm::mat4{ 1.0f }, position) *
            glm::rotate(glm::mat4{ 1.0f }, rotation, glm::vec3{ 0.0f, 0.0f, 1.0f }) *
            glm::scale(glm::mat4{ 1.0f }, glm::vec3{ size.x, size.y, 1.0f });
    data.shader->setMat4("v_uTransform", transform);

    data.quadVertexArray->bind();
    RenderCommand::drawIndexed(data.quadVertexArray);
}

void Renderer2D::drawRotatedQuad(const glm::vec2& position, const glm::vec2& size, float rotation, Ref<Texture2D> texture, float tilingFactor, const glm::vec4& tintColor) {
    drawRotatedQuad(glm::vec3{ position.x, position.y, 0.0f }, size, rotation, texture, tilingFactor, tintColor);
}

void Renderer2D::drawRotatedQuad(const glm::vec3& position, const glm::vec2& size, float rotation, Ref<Texture2D> texture, float tilingFactor, const glm::vec4& tintColor) {
    NAVIA_PROFILE_FUNCTION();

    data.shader->setFloat4("f_uColor", tintColor);
    data.shader->setFloat("f_uTilingFactor", tilingFactor);
    texture->bind();

    glm::mat4 transform =
            glm::translate(glm::mat4{ 1.0f }, position) *
            glm::rotate(glm::mat4{ 1.0f }, rotation, glm::vec3{ 0.0f, 0.0f, 1.0f }) *
            glm::scale(glm::mat4{ 1.0f }, glm::vec3{ size.x, size.y, 1.0f });
    data.shader->setMat4("v_uTransform", transform);

    data.quadVertexArray->bind();
    RenderCommand::drawIndexed(data.quadVertexArray);
}
}