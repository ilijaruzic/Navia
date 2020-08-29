#include "navia/platform/opengl/OpenGLFramebuffer.hpp"
#include "navia/renderer/Framebuffer.hpp"
#include "navia/renderer/Renderer.hpp"

namespace Navia {
Ref<Framebuffer> Framebuffer::create(const FramebufferProperties& properties) {
    switch (Renderer::getRendererAPI()) {
        case RendererAPI::APIVendor::None:
            NAVIA_CORE_ASSERT(false, "API not supported yet!");
            break;
        case RendererAPI::APIVendor::OpenGL:
            return createRef<OpenGLFramebuffer>(properties);
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