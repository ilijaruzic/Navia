#ifndef _FRAMEBUFFER_HPP_
#define _FRAMEBUFFER_HPP_

#include "navia/core/Base.hpp"

namespace Navia {
struct FramebufferProperties {
    size_t width;
    size_t height;
    size_t samples{ 1 };

    bool swapChainTarget{ false };

};

class Framebuffer {
public:
    static Ref<Framebuffer> create(const FramebufferProperties& properties);
    virtual ~Framebuffer() = default;

    virtual const FramebufferProperties& getProperties() const = 0;
    virtual size_t getColorAttachment() const = 0;

    virtual void bind() = 0;
    virtual void unbind() = 0;

    virtual void resize(size_t width, size_t height) = 0;
};
}

#endif