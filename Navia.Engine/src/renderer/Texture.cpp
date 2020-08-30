#include "navia/renderer/Renderer.hpp"
#include "navia/renderer/Texture.hpp"
#include "navia/platform/opengl/OpenGLTexture.hpp"

namespace Navia {
Ref<Texture2D> Texture2D::create(uint32_t width, uint32_t height) {
    switch (Renderer::getRendererAPI()) {
        case RendererAPI::APIVendor::None:
            NAVIA_CORE_ASSERT(false, "API not supported yet!");
            break;
        case RendererAPI::APIVendor::OpenGL:
            return createRef<OpenGLTexture2D>(width, height);
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

Ref<Texture2D> Texture2D::create(const std::string& filepath) {
    switch (Renderer::getRendererAPI()) {
        case RendererAPI::APIVendor::None:
        NAVIA_CORE_ASSERT(false, "API not supported yet!");
            break;
        case RendererAPI::APIVendor::OpenGL:
            return createRef<OpenGLTexture2D>(filepath);
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