#ifndef _OPENGL_RENDERER_API_HPP_
#define _OPENGL_RENDERER_API_HPP_

#include "navia/renderer/RendererAPI.hpp"

namespace Navia {
class OpenGLRendererAPI : public RendererAPI {
public:
    void init() override;
    void shutdown() override;
    void setViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) override;
    void setClearColor(const glm::vec4& color) override;
    void clear() override;
    void drawIndexed(Ref<VertexArray> vertexArray, uint32_t indexCount) override;
};
}

#endif