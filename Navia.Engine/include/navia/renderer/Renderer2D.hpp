#ifndef _RENDERER_2D_HPP_
#define _RENDERER_2D_HPP_

#include "navia/core/Base.hpp"
#include "navia/renderer/Camera.hpp"
#include "navia/renderer/OrthographicCamera.hpp"
#include "navia/renderer/Texture.hpp"
#include <glm/glm.hpp>

namespace Navia {
class Renderer2D {
public:
    static void init();
    static void shutdown();

    static void beginScene(const Camera& camera, const glm::mat4& transform);
    static void beginScene(const OrthographicCamera& camera); // TODO: Remove
    static void endScene();

    static void flush();

    static void drawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color);
    static void drawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color);
    static void drawQuad(const glm::mat4& transform, const glm::vec4& color);
    static void drawQuad(const glm::vec2& position, const glm::vec2& size, Ref<Texture2D> texture, float tilingFactor = 1.0f, const glm::vec4& tintColor = glm::vec4{ 1.0f });
    static void drawQuad(const glm::vec3& position, const glm::vec2& size, Ref<Texture2D> texture, float tilingFactor = 1.0f, const glm::vec4& tintColor = glm::vec4{ 1.0f });
    static void drawQuad(const glm::mat4& transform, Ref<Texture2D> texture, float tilingFactor = 1.0f, const glm::vec4& tintColor = glm::vec4{ 1.0f });

    static void drawRotatedQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const glm::vec4& color);
    static void drawRotatedQuad(const glm::vec3& position, const glm::vec2& size, float rotation, const glm::vec4& color);
    static void drawRotatedQuad(const glm::mat4& transform, float rotation, const glm::vec4& color);
    static void drawRotatedQuad(const glm::vec2& position, const glm::vec2& size, float rotation, Ref<Texture2D> texture, float tilingFactor = 1.0f, const glm::vec4& tintColor = glm::vec4{ 1.0f });
    static void drawRotatedQuad(const glm::vec3& position, const glm::vec2& size, float rotation, Ref<Texture2D> texture, float tilingFactor = 1.0f, const glm::vec4& tintColor = glm::vec4{ 1.0f });
    static void drawRotatedQuad(const glm::mat4& transform, float rotation, Ref<Texture2D> texture, float tilingFactor = 1.0f, const glm::vec4& tintColor = glm::vec4{ 1.0f });

    struct Renderer2DStatistics {
        uint32_t drawCallCount = 0;
        uint32_t quadCount = 0;

        uint32_t getVertexCount() const;
        uint32_t getIndexCount() const;
    };
    static Renderer2DStatistics getStatistics();
    static void resetStatistics();

private:
    static void flushAndReset();
};
}

#endif