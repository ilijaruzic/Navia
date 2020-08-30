#include "navia/platform/opengl/OpenGLIndexBuffer.hpp"
#include "navia/renderer/IndexBuffer.hpp"
#include "navia/renderer/Renderer.hpp"

namespace Navia {
Ref<IndexBuffer> IndexBuffer::create(uint32_t* indices, uint32_t size) {
    switch (Renderer::getRendererAPI()) {
        case RendererAPI::APIVendor::None:
            NAVIA_CORE_ASSERT(false, "API not supported yet!");
            break;
        case RendererAPI::APIVendor::OpenGL:
            return createRef<OpenGLIndexBuffer>(indices, size);
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