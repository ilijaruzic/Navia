#ifndef _RENDER_COMMAND_HPP_
#define _RENDER_COMMAND_HPP_

#include "navia/renderer/VertexArray.hpp"
#include "navia/renderer/RendererAPI.hpp"

namespace Navia {
class RenderCommand {
public:
    static void init();
    static void setViewport(size_t x, size_t y, size_t width, size_t height);
    static void setClearColor(const glm::vec4& color);
    static void clear();
    static void drawIndexed(Ref<VertexArray> vertexArray);

public:
    static RendererAPI* rendererAPI;
};
}

#endif