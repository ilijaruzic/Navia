#include "navia/renderer/Renderer.hpp"
#include "navia/renderer/Shader.hpp"
#include "navia/platform/opengl/OpenGLShader.hpp"

namespace Navia {
Ref<Shader> Shader::create(const std::string& filepath) {
    switch (Renderer::getRendererAPI()) {
        case RendererAPI::APIVendor::None:
        NAVIA_CORE_ASSERT(false, "API not supported yet!");
            break;
        case RendererAPI::APIVendor::OpenGL:
            return createRef<OpenGLShader>(filepath);
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

Ref<Shader> Shader::create(const std::string& name, const std::string& vertexSource, const std::string& fragmentSource) {
    switch (Renderer::getRendererAPI()) {
        case RendererAPI::APIVendor::None:
        NAVIA_CORE_ASSERT(false, "API not supported yet!");
            break;
        case RendererAPI::APIVendor::OpenGL:
            return createRef<OpenGLShader>(name, vertexSource, fragmentSource);
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