#include "navia/renderer/VertexArray.hpp"
#include "navia/renderer/Renderer.hpp"
#include "navia/platform/opengl/OpenGLVertexArray.hpp"

namespace Navia {
VertexArray* VertexArray::create() {
    switch (Renderer::getRendererAPI()) {
        case RendererAPI::APIVendor::None:
        NAVIA_CORE_ASSERT(false, "API not supported yet!");
            break;
        case RendererAPI::APIVendor::OpenGL:
            return new OpenGLVertexArray();
        case RendererAPI::APIVendor::Direct3D:
        NAVIA_CORE_ASSERT(false, "API not supported yet!");
            break;
        case RendererAPI::APIVendor::Metal:
        NAVIA_CORE_ASSERT(false, "API not supported yet!");
            break;
        case RendererAPI::APIVendor::Vulkan:
        NAVIA_CORE_ASSERT(false, "API not supported yet!");
            break;
    }
    NAVIA_CORE_ASSERT(false, "Unknown API!");
    return nullptr;
}
}