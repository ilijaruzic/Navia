#ifndef _OPENGL_RENDERER_API_HPP_
#define _OPENGL_RENDERER_API_HPP_

#include "navia/renderer/RendererAPI.hpp"

namespace Navia {
class OpenGLRendererAPI : public RendererAPI {
public:
    void setClearColor(const glm::vec4& color) override;
    void clear() override;
    void drawIndexed(Ref<VertexArray> vertexArray) override;
};
}

#endif