#ifndef _RENDERER_HPP_
#define _RENDERER_HPP_

#include "navia/renderer/OrthographicCamera.hpp"
#include "navia/renderer/RendererAPI.hpp"
#include "navia/renderer/VertexArray.hpp"
#include "navia/renderer/Shader.hpp"

namespace Navia {
class Renderer {
public:
    static RendererAPI::APIVendor getRendererAPI();

    static void beginScene(OrthographicCamera& camera);
    static void endScene();

    static void submit(Ref<Shader> shader, Ref<VertexArray> vertexArray, const glm::mat4& transform = glm::mat4{ 1.0f });

private:
    struct SceneData {
        glm::mat4 viewProjectionMatrix;
    };
    static SceneData* data;
};
}

#endif