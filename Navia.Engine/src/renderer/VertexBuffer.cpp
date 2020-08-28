#include "navia/platform/opengl/OpenGLVertexBuffer.hpp"
#include "navia/renderer/Renderer.hpp"
#include "navia/renderer/VertexBuffer.hpp"

namespace Navia {
Ref<VertexBuffer> VertexBuffer::create(size_t size) {
    switch (Renderer::getRendererAPI()) {
        case RendererAPI::APIVendor::None:
            NAVIA_CORE_ASSERT(false, "API not supported yet!");
            break;
        case RendererAPI::APIVendor::OpenGL:
            return createRef<OpenGLVertexBuffer>(size);
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

Ref<VertexBuffer> VertexBuffer::create(float* vertices, size_t size) {
    switch (Renderer::getRendererAPI()) {
        case RendererAPI::APIVendor::None:
            NAVIA_CORE_ASSERT(false, "API not supported yet!");
            break;
        case RendererAPI::APIVendor::OpenGL:
            return createRef<OpenGLVertexBuffer>(vertices, size);
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