#ifndef _RENDERER_API_HPP_
#define _RENDERER_API_HPP_

#include "navia/renderer/VertexArray.hpp"
#include <glm/glm.hpp>

namespace Navia {
class RendererAPI {
public:
    enum class APIVendor {
        None        = 0,
        OpenGL      = 1,
        Direct3D    = 2,
        Metal       = 3,
        Vulkan      = 4
    };

    virtual ~RendererAPI() = default;

    static APIVendor getAPIVendor();

    virtual void init() = 0;
    virtual void shutdown() = 0;
    virtual void setViewport(size_t x, size_t y, size_t width, size_t height) = 0;
    virtual void setClearColor(const glm::vec4& color) = 0;
    virtual void clear() = 0;
    virtual void drawIndexed(Ref<VertexArray> vertexArray) = 0;

private:
    static APIVendor API;
};
}

#endif