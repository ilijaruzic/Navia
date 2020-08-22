#include "navia/renderer/RendererAPI.hpp"

namespace Navia {
RendererAPI::APIVendor RendererAPI::API = RendererAPI::APIVendor::OpenGL;

RendererAPI::APIVendor RendererAPI::getAPIVendor() {
    return API;
}
}