#ifndef _RENDER_COMMAND_HPP_
#define _RENDER_COMMAND_HPP_

#include "navia/renderer/VertexArray.hpp"
#include "navia/renderer/RendererAPI.hpp"

namespace Navia {
class RenderCommand {
public:
    static void init();
    static void shutdown();
    static void setViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height);
    static void setClearColor(const glm::vec4& color);
    static void clear();
    static void drawIndexed(Ref<VertexArray> vertexArray, uint32_t indexCount = 0);

public:
    static Scope<RendererAPI> rendererAPI;
};
}

#endif